Allows you to build a list of [NanoVg] rendering commands to be executued later, elsewhere or repeatably such as another thread.

Single header, only dependencies are nanovg, cstdint, std::string, std::vector

## Example
Example - lock free submission of nanovg draw commands from a second thread.
```
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

Buffers can be reused. `NanoVgCommandBuffer` doesn't need to see a nanovg context, it just stores commands to be executed when `dispatch` is called.

## Including
This is a single header library. To use:
```
#include "nanovg_command_buffer.hpp"
```
and in one file:
```
#define NANOVG_COMMAND_BUFFER_IMPL
#include "nanovg_command_buffer.hpp"
```

If you are using a port that uses a global nanovg context (eg, you call `nvgEndFrame()` instead of `nvgEndFrame(vg)`, such as the [bgfx] port) then you must also define:
```
#define NANOVG_COMMAND_BUFFER_GLOBAL_CONTEXT
#define NANOVG_COMMAND_BUFFER_IMPL
#include "nanovg_command_buffer.hpp"
```
and call dispatch(NULL) to use.


## Full API
```
class NanoVgCommandBuffer;

void swap(NanoVgCommandBuffer& other); // swaps internal std::vectors
void clear(); // 
void dispatchSingle(NVGcontext* ctx, const NanoVgCommandBuffer::command & c);
void dispatch(NVGcontext* ctx)

inline void nvgGlobalCompositeOperation(int op)
inline void nvgGlobalCompositeBlendFunc(int sfactor, int dfactor)
inline void nvgGlobalCompositeBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)
inline void nvgSave()
inline void nvgRestore()
inline void nvgReset()
inline void nvgShapeAntiAlias(int enabled)
inline void nvgStrokeColor(NVGcolor color)
inline void nvgStrokePaint(NVGpaint paint)
inline void nvgFillColor(NVGcolor color)
inline void nvgFillPaint(NVGpaint paint)
inline void nvgMiterLimit(float limit)
inline void nvgStrokeWidth(float size)
inline void nvgLineCap(int cap)
inline void nvgLineJoin(int join)
inline void nvgGlobalAlpha(float alpha)
inline void nvgResetTransform()
inline void nvgTransform(float a, float b, float c, float d, float e, float f)
inline void nvgTranslate(float x, float y)
inline void nvgRotate(float angle)
inline void nvgSkewX(float angle)
inline void nvgSkewY(float angle)
inline void nvgScale(float x, float y)
inline void nvgScissor(float x, float y, float  w, float h)
inline void nvgIntersectScissor(float x, float y, float w, float h)
inline void nvgResetScissor()
inline void nvgBeginPath()
inline void nvgMoveTo(float x, float y)
inline void nvgLineTo(float x, float y)
inline void nvgBezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y)
inline void nvgQuadTo(float cx, float cy, float x, float y)
inline void nvgArcTo(float cx, float cy, float x, float y, float radius)
inline void nvgClosePath()
inline void nvgPathWinding(int dir)
inline void nvgArc(float cx, float cy, float r, float a0, float a1, int dir)
inline void nvgRect(float x, float y, float w, float h)
inline void nvgRoundedRect(float x, float y, float w, float h, float r)
inline void nvgEllipse(float cx, float cy, float rx, float ry)
inline void nvgCircle(float cx, float cy, float r)
inline void nvgFill()
inline void nvgStroke()
inline void nvgFontSize(float size)
inline void nvgFontBlur(float blur)
inline void nvgTextLetterSpacing(float spacing)
inline void nvgTextLineHeight(float lineHeight)
inline void nvgTextAlign(int align)
inline void nvgFontFaceId(int font)
inline void nvgText(float x, float y, const char* string, const char* end)
inline void nvgTextBox(float x, float y, float breakRowWidth, const char* string, const char* end)
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
