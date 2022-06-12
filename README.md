# NanoVg Command Buffer
Allows you to build a list of [NanoVg](https://github.com/memononen/nanovg) rendering commands to be executued later/elsewhere/repeatably. One use case is to render from another thread.

Single header, only dependencies are nanovg, cstdint, std::string, std::vector

This also supports [sdl_stb_font](https://github.com/SnapperTT/sdl_stb_font) producer consumer frontend integration, use `#define SDL_STB_PRODUCER_CONSUMER` to enable.

## Example
Example - lock free submission of nanovg draw commands from a second thread.
```c++
// Thread 1 (update thread)
NanoVgCommandBuffer* buff = new NanoVgCommandBuffer; // you don't need to use heap, its just easier to pass between threads
buff->nvgBeginPath();
buff->nvgRect(100,100, 120,30);
buff->nvgFillColor(nvgRGBA(255,192,0,255));
buff->nvgFill();

mConcurrentQueue.enqueue(buff); // using moodycamel::BlockingConcurrentQueue to pass ownership between threads
buff = NULL;

// Thread 2 (render thread)
NanoVgCommandBuffer* buff = NULL;
mConcurrentQueue.dequeue(buff)

nvgBeginFrame(vg, windowW , windowH, (float)windowW / ( float)windowH);

if (buff) {
	buff->dispatch(vg); // actually executes the commands
	delete buff; // if you're done with it, otherwise keep and reuse it
	}
	
nvgEndFrame(vg);
``` 

Buffers can be reused. `NanoVgCommandBuffer` doesn't need to see a nanovg context nor does it care about nanovg's internal state, it just stores commands to be executed when `dispatch(vg)` is called.

## Including
This is a single header library. To use:
```c++
#include "nanovg_command_buffer.hpp"
```
and in one file:
```c++
#define NANOVG_COMMAND_BUFFER_IMPL
#include "nanovg_command_buffer.hpp"
```


## Full API
```c++
class NanoVgCommandBuffer;

void swap(NanoVgCommandBuffer& other); // swaps internal std::vectors
void clear(); // 
void dispatchSingle(NVGcontext* ctx, const NanoVgCommandBuffer::command & c);
void dispatch(NVGcontext* ctx);

// nvg functions
// nvg composite
void nvgGlobalCompositeOperation(int op);
void nvgGlobalCompositeBlendFunc(int sfactor, int dfactor);
void nvgGlobalCompositeBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);

// nvg state
void nvgSave();
void nvgRestore();
void nvgReset();

// nvg style
void nvgShapeAntiAlias(int enabled);
void nvgStrokeColor(NVGcolor color);
void nvgStrokePaint(NVGpaint paint);
void nvgFillColor(NVGcolor color);
void nvgFillPaint(NVGpaint paint);
void nvgMiterLimit(float limit);
void nvgStrokeWidth(float size);
void nvgLineCap(int cap);
void nvgLineJoin(int join);
void nvgGlobalAlpha(float alpha);

// nvg transform
void nvgResetTransform();
void nvgTransform(float a, float b, float c, float d, float e, float f);
void nvgTranslate(float x, float y);
void nvgRotate(float angle);
void nvgSkewX(float angle);
void nvgSkewY(float angle);
void nvgScale(float x, float y);

// nvg scissor
void nvgScissor(float x, float y, float  w, float h);
void nvgIntersectScissor(float x, float y, float w, float h);
void nvgResetScissor();

//nvg path
void nvgBeginPath();
void nvgMoveTo(float x, float y);
void nvgLineTo(float x, float y);
void nvgBezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);
void nvgQuadTo(float cx, float cy, float x, float y);
void nvgArcTo(float cx, float cy, float x, float y, float radius);
void nvgClosePath();
void nvgPathWinding(int dir);
void nvgArc(float cx, float cy, float r, float a0, float a1, int dir);
void nvgRect(float x, float y, float w, float h);
void nvgRoundedRect(float x, float y, float w, float h, float r);
void nvgEllipse(float cx, float cy, float rx, float ry);
void nvgCircle(float cx, float cy, float r);
void nvgFill();
void nvgStroke();

// nvg font
void nvgFontSize(float size);
void nvgFontBlur(float blur);
void nvgTextLetterSpacing(float spacing);
void nvgTextLineHeight(float lineHeight);
void nvgTextAlign(int align);
void nvgFontFaceId(int font);
void nvgText(float x, float y, const char* string, const char* end);
void nvgTextBox(float x, float y, float breakRowWidth, const char* string, const char* end);
```

### Usage Notes
- NVGpaint instances will be reusued if the same one is used *sequentially*.
- Text functions store a copy of the string to be drawn. You can safely discard a string after calling nvgText, etc

### Unsupported functions
- nvgRoundedRectVarying - has too many args. I might add it if someone wants it
- nvgFontFace  - use nvgFontFaceId instead
- Most functions that returns a value. This lib can only be used to set states, not query them

## License
Public Domain
