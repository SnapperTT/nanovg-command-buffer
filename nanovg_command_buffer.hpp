#ifndef NANOVG_COMMAND_BUFFER_HPP
#define NANOVG_COMMAND_BUFFER_HPP

#include <cstdint>

#ifndef NCBH_STRING
	#include <string>
	#define NCBH_STRING std::string
#endif
#ifndef NCBH_VECTOR
	#include <vector>
	#define NCBH_VECTOR std::vector
#endif
#ifndef NCBH_PAGEQUEUE
	#define NCBH_PAGEQUEUE NCBH_VECTOR
	#ifndef NCBH_PAGEQUEUE_RANDOM_ACCESS
		#define NCBH_PAGEQUEUE_RANDOM_ACCESS 1
	#endif
#else
	#ifndef NCBH_PAGEQUEUE_RANDOM_ACCESS
		#define NCBH_PAGEQUEUE_RANDOM_ACCESS 0
	#endif
#endif

struct sttfont_formatted_text;
struct sttfont_format;
class NanoVgCommandBufferCustomCallbackI;

struct NCB_Constants {
	static constexpr int32_t NCB_unknown = 0;
	
	// composite
	static constexpr int32_t NCB_nvgGlobalCompositeOperation = 1;
	static constexpr int32_t NCB_nvgGlobalCompositeBlendFunc = 2;
	static constexpr int32_t NCB_nvgGlobalCompositeBlendFuncSeparate = 3;
	
	// state
	static constexpr int32_t NCB_nvgSave = 4;
	static constexpr int32_t NCB_nvgRestore = 5;
	static constexpr int32_t NCB_nvgReset = 6;
	
	// style
	static constexpr int32_t NCB_nvgShapeAntiAlias = 7;
	static constexpr int32_t NCB_nvgStrokeColor = 8;
	static constexpr int32_t NCB_nvgStrokePaint = 9;
	static constexpr int32_t NCB_nvgFillColor = 10;
	static constexpr int32_t NCB_nvgFillPaint = 11;
	static constexpr int32_t NCB_nvgMiterLimit = 12;
	static constexpr int32_t NCB_nvgStrokeWidth = 13;
	static constexpr int32_t NCB_nvgLineCap = 14;
	static constexpr int32_t NCB_nvgLineJoin = 15;
	static constexpr int32_t NCB_nvgGlobalAlpha = 16;
	
	// transform
	static constexpr int32_t NCB_nvgResetTransform = 17;
	static constexpr int32_t NCB_nvgTransform = 18;
	static constexpr int32_t NCB_nvgTranslate = 19;
	static constexpr int32_t NCB_nvgRotate = 49;
	static constexpr int32_t NCB_nvgSkewX = 20;
	static constexpr int32_t NCB_nvgSkewY = 21;
	static constexpr int32_t NCB_nvgScale = 22;
			
	// scissor
	static constexpr int32_t NCB_nvgScissor = 23;
	static constexpr int32_t NCB_nvgIntersectScissor = 24;
	static constexpr int32_t NCB_nvgResetScissor = 25;
	
	// path
	static constexpr int32_t NCB_nvgBeginPath = 26;
	static constexpr int32_t NCB_nvgMoveTo = 27;
	static constexpr int32_t NCB_nvgLineTo = 28;
	static constexpr int32_t NCB_nvgBezierTo = 29;
	static constexpr int32_t NCB_nvgQuadTo = 30;
	static constexpr int32_t NCB_nvgArcTo = 31;
	static constexpr int32_t NCB_nvgClosePath = 32;
	
	// stroke
	static constexpr int32_t NCB_nvgPathWinding = 33;
	static constexpr int32_t NCB_nvgArc = 34;
	static constexpr int32_t NCB_nvgRect = 35;
	static constexpr int32_t NCB_nvgRoundedRect = 36;
	static constexpr int32_t NCB_nvgEllipse = 37;
	static constexpr int32_t NCB_nvgCircle = 38;
	static constexpr int32_t NCB_nvgFill = 39;
	static constexpr int32_t NCB_nvgStroke = 40;
	
	// text
	static constexpr int32_t NCB_nvgFontSize = 41;
	static constexpr int32_t NCB_nvgFontBlur = 42;
	static constexpr int32_t NCB_nvgTextLetterSpacing = 43;
	static constexpr int32_t NCB_nvgTextLineHeight = 44;
	static constexpr int32_t NCB_nvgTextAlign = 45;
	static constexpr int32_t NCB_nvgFontFaceId = 46;
	static constexpr int32_t NCB_nvgText = 47;
	static constexpr int32_t NCB_nvgTextBox = 48;
	
	// break
	static constexpr int32_t NCB_pause = 1000;
	
	// sdlStbFont Stuff
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawText = 1001;
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawPrerendered = 1002;
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod = 1003;
	static constexpr int32_t SSF_BGFX_SET_SCISSOR = 1004;
	static constexpr int32_t SSF_BGFX_CLEAR_SCISSOR = 1005;
	
	// custom engine stuff
	};
	
struct nvgw {
	// For sttr registering with a namespace
	inline static NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) {
		return ::nvgRGB(r, g, b);
		}
	inline static NVGcolor nvgRGBf(float r, float g, float b) {
		return ::nvgRGBf(r, g, b);
		}
	inline static NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		return ::nvgRGBA(r, g, b, a);
		}
	inline static NVGcolor nvgRGBAf(float r, float g, float b, float a) {
		return ::nvgRGBAf(r, g, b, a);
		}
	inline static NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u) {
		return ::nvgLerpRGBA(c0, c1, u);
		}
	inline static NVGcolor nvgTransRGBA(NVGcolor c0, unsigned char a) {
		return ::nvgTransRGBA(c0, a);
		}
	inline static NVGcolor nvgTransRGBAf(NVGcolor c0, float a) {
		return ::nvgTransRGBAf(c0, a);
		}
	inline static NVGcolor nvgHSL(float h, float s, float l) {
		return ::nvgHSL(h, s, l);
		}
	inline static NVGcolor nvgHSLA(float h, float s, float l, unsigned char a) {
		return ::nvgHSLA(h, s, l, a);
		}

	inline static NVGpaint nvgLinearGradient(NVGcontext* ctx, float sx, float sy, float ex, float ey, NVGcolor icol, NVGcolor ocol) {
		return ::nvgLinearGradient(ctx, sx, sy, ex, ey, icol, ocol);
		}
	inline static NVGpaint nvgBoxGradient(NVGcontext* ctx, float x, float y, float w, float h, float r, float f, NVGcolor icol, NVGcolor ocol) {
		return  ::nvgBoxGradient(ctx, x, y, w, h, r, f, icol, ocol);
		}
	inline static NVGpaint nvgRadialGradient(NVGcontext* ctx, float cx, float cy, float inr, float outr, NVGcolor icol, NVGcolor ocol) {
		return ::nvgRadialGradient(ctx, cx, cy, inr, outr, icol, ocol);
		}
	};

class NanoVgCommandBuffer {
public:
	struct command
	{
		int32_t functionIdx;
		union
		{
			float (argsFloats) [7];
			int32_t (argsInts) [7];
		} data;
		
		inline command () {}	
		inline command (const int32_t _id) : functionIdx(_id) {}
		inline explicit command (const int32_t _id, const float f0) : functionIdx(_id) { data.argsFloats[0] = f0; }
		inline explicit command (const int32_t _id, const float f0, const float f1) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const float f3) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsFloats[3] = f3; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const float f3, const float f4) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsFloats[3] = f3; data.argsFloats[4] = f4; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const float f3, const float f4, const float f5) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsFloats[3] = f3; data.argsFloats[4] = f4; data.argsFloats[5] = f5; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const float f3, const float f4, const int i5) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsFloats[3] = f3; data.argsFloats[4] = f4; data.argsInts[5] = i5; }
		inline explicit command (const int32_t _id, const int i0) : functionIdx(_id) { data.argsInts[0] = i0; }
		inline explicit command (const int32_t _id, const int i0, const int i1) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3, const int i4) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; data.argsInts[4] = i4; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3, const int i4, const int i5) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; data.argsInts[4] = i4; data.argsInts[5] = i5; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3, const int i4, const int i5, const int i6) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; data.argsInts[4] = i4; data.argsInts[5] = i5; data.argsInts[6] = i6; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const int i2) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsInts[2] = i2; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const int i3) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsInts[3] = i3; }
	};
	NCBH_PAGEQUEUE <NanoVgCommandBuffer::command> mCommands;
	NCBH_VECTOR <NVGpaint> mPaints;
	NCBH_VECTOR <NCBH_STRING> mStrings;
	//NCBH_VECTOR <NVGvertex> mPoints;
	#ifdef SDL_STB_PRODUCER_CONSUMER
	producer_consumer_font_cache* m_producer_consumer_font_cache;
	#endif
	NanoVgCommandBufferCustomCallbackI* customCommandHandler;
	int pauseCode;
	int instructionCounter;
		
protected:
	int addPaint (NVGpaint const & paint);
	int addString (char const * string, char const * end);
public:
	NanoVgCommandBuffer();
	void swap (NanoVgCommandBuffer & other);
	void clear ();
	void dispatchSingle (NVGcontext * ctx, NanoVgCommandBuffer::command const & c);
	void dispatch (NVGcontext * ctx);
	static void sttr_register();

	// Pauses rendering and sets this->pauseCode to _pauseCode
	inline void pause(int _pauseCode) {
		mCommands.push_back(command(NCB_Constants::NCB_pause, _pauseCode));
		}

	// nvg composite
	inline void nvgGlobalCompositeOperation(int op) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgGlobalCompositeOperation, op));
		}
	inline void nvgGlobalCompositeBlendFunc(int sfactor, int dfactor) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgGlobalCompositeBlendFunc, sfactor, dfactor));
		}
	inline void nvgGlobalCompositeBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgGlobalCompositeBlendFuncSeparate, srcRGB, dstRGB, srcAlpha, dstAlpha));
		}
		
	// nvg state
	inline void nvgSave() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgSave));
		}
	inline void nvgRestore() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgRestore));
		}
	inline void nvgReset() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgReset));
		}
		
	// nvg styles
	inline void nvgShapeAntiAlias(int enabled) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgShapeAntiAlias, enabled));
		}
	inline void nvgStrokeColor(NVGcolor color) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgStrokeColor, color.r, color.g, color.b, color.a));
		}
	inline void nvgStrokePaint(NVGpaint paint) {
		int idx = addPaint(paint);
		mCommands.push_back(command(NCB_Constants::NCB_nvgStrokePaint, idx));
		}
	inline void nvgFillColor(NVGcolor color) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgFillColor, color.r, color.g, color.b, color.a));
		}
	inline void nvgFillPaint(NVGpaint paint) {
		int idx = addPaint(paint);
		mCommands.push_back(command(NCB_Constants::NCB_nvgFillPaint, idx));
		}
	inline void nvgMiterLimit(float limit) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgMiterLimit, limit));
		}
	inline void nvgStrokeWidth(float size) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgStrokeWidth, size));
		}
	inline void nvgLineCap(int cap) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgLineCap, cap));
		}
	inline void nvgLineJoin(int join) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgLineJoin, join));
		}
	inline void nvgGlobalAlpha(float alpha) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgGlobalAlpha, alpha));
		}

	// nvg transforms
	inline void nvgResetTransform() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgResetTransform));
		}
	inline void nvgTransform(float a, float b, float c, float d, float e, float f) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgTransform, a, b, c, d, e, f));
		}
	inline void nvgTranslate(float x, float y) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgTranslate, x, y));
		}
	inline void nvgRotate(float angle) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgRotate, angle));
		}
	inline void nvgSkewX(float angle) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgSkewX, angle));
		}
	inline void nvgSkewY(float angle) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgSkewY, angle));
		}
	inline void nvgScale(float x, float y) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgScale, x, y));
		}


	// nvg scissor
	inline void nvgScissor(float x, float y, float  w, float h) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgScissor, x, y, w, h));
		}
	inline void nvgIntersectScissor(float x, float y, float w, float h) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgIntersectScissor, x, y, w, h));
		}
	inline void nvgResetScissor() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgResetScissor));
		}
	
	// nvg path
	inline void nvgBeginPath() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgBeginPath));
		}
	inline void nvgMoveTo(float x, float y) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgMoveTo, x, y));
		}
	inline void nvgLineTo(float x, float y) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgLineTo, x, y));
		}
	inline void nvgBezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgBezierTo, c1x, c1y, c2x, c2y, x, y));
		}
	inline void nvgQuadTo(float cx, float cy, float x, float y) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgQuadTo, cx, cy, x, y));
		}
	inline void nvgArcTo(float cx, float cy, float x, float y, float radius) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgArcTo, cx, cy, x, y, radius));
		}
	inline void nvgClosePath() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgClosePath));
		}
		
	inline void nvgPathWinding(int dir) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgPathWinding, dir));
		}
	inline void nvgArc(float cx, float cy, float r, float a0, float a1, int dir) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgArc, cx, cy, r, a0, a1, dir));
		}
	inline void nvgRect(float x, float y, float w, float h) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgRect, x, y, w, h));
		}
	inline void nvgRoundedRect(float x, float y, float w, float h, float r) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgRoundedRect, x, y, w, h, r));
		}
	//inline void nvgRoundedRectVarying(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft) {
	//	abort();
	//	}
	inline void nvgEllipse(float cx, float cy, float rx, float ry) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgEllipse, cx, cy, rx, ry));
		}
	inline void nvgCircle(float cx, float cy, float r) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgEllipse, cx, cy, r));
		}
	inline void nvgFill() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgFill));
		}
	inline void nvgStroke() {
		mCommands.push_back(command(NCB_Constants::NCB_nvgStroke));
		}
	
	// text
	inline void nvgFontSize(float size) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgFontSize, size));
		}
	inline void nvgFontBlur(float blur) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgFontBlur, blur));
		}
	inline void nvgTextLetterSpacing(float spacing) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgTextLetterSpacing, spacing));
		}
	inline void nvgTextLineHeight(float lineHeight) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgTextLineHeight, lineHeight));
		}
	inline void nvgTextAlign(int align) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgTextAlign, align));
		}
	inline void nvgFontFaceId(int font) {
		mCommands.push_back(command(NCB_Constants::NCB_nvgFontFaceId, font));
		}
	//void nvgFontFace(const char* font) {	// Don't use this, use nvgFontFaceId instead
	//	mCommands.push_back(command(NCB_Constants::NCB_nvgFontFace, font));
	//	}
	
	inline void nvgText(float x, float y, const char* string, const char* end) {
		int idx = addString(string, end);
		mCommands.push_back(command(NCB_Constants::NCB_nvgText, x, y, idx));
		}
	inline void nvgTextBox(float x, float y, float breakRowWidth, const char* string, const char* end) {
		int idx = addString(string, end);
		mCommands.push_back(command(NCB_Constants::NCB_nvgTextBox, x, y, breakRowWidth, idx));
		}
		
	#ifdef SDL_STB_PRODUCER_CONSUMER
	// SDL_STB_PRODUCER_CONSUMER_Font functions to be used with producerConsumerFrontend
	// https://github.com/SnapperTT/sdl_stb_font
	inline void pushSsfText(const int h) {
		mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText, h));
		}
	
	void pushSsfText(const int x, const int y, const NCBH_STRING & s, int* xOut=NULL, int * widthOut=NULL, int* heightOut=NULL);
		
	void pushSsfText(const int x, const int y, const sttfont_formatted_text & s, int* xOut=NULL, int * widthOut=NULL, int* heightOut=NULL);
		
	void pushSsfText(const int x, const int y, const char* c, int* xOut=NULL, int * widthOut=NULL, int* heightOut=NULL);
	
	void pushSsfText(const int x, const int y, const sttfont_format & format, const char* c, int* xOut=NULL, int * widthOut=NULL, int* heightOut=NULL);
	
	void pushSsfText(const int x, const int y, const sttfont_format & format, const NCBH_STRING & s, int* xOut=NULL, int * widthOut=NULL, int* heightOut=NULL);
		
	void pushSsfPrerendered(const int textHandle, const int x, const int y);
	
	void pushSsfPrerenderedWColorMod(const int textHandle, const int x, const int y, const int r, const int g, const int b, const int a);
	#endif
	
	#ifdef BGFX
	inline void ssfBgfxSetScissor(const float x, const float y, const float w, const float h) {
		mCommands.push_back(command(NCB_Constants::SSF_BGFX_SET_SCISSOR, x, y, w, h));
		}
	inline void ssfBgfxClearScissor() {
		mCommands.push_back(command(NCB_Constants::SSF_BGFX_CLEAR_SCISSOR));
		}
	#endif
	
	inline void push_custom(command&& c) {
		mCommands.push_back(std::move(c));
		}
		
	inline void push_custom(const command& c) {
		mCommands.push_back(c);
		}
	};

	
class NanoVgCommandBufferCustomCallbackI {
public:
	virtual inline bool handleCustomCallback(NanoVgCommandBuffer * NVG, NVGcontext * ctx, NanoVgCommandBuffer::command const & c) {
		return true;
		}
	};
#endif

#ifdef NANOVG_COMMAND_BUFFER_IMPL
NanoVgCommandBuffer::NanoVgCommandBuffer() {
	#ifdef SDL_STB_PRODUCER_CONSUMER
		m_producer_consumer_font_cache = NULL;
	#endif
	
	pauseCode = 0;
	instructionCounter = 0;
	customCommandHandler = NULL;
	}
	
int NanoVgCommandBuffer::addPaint (NVGpaint const & paint) {
	if (mPaints.size()) {
		// easy out - resusue paint if its the same as previous
		if (memcmp(&mPaints[mPaints.size()-1], &paint, sizeof(NVGpaint)) == 0)
			return mPaints.size()-1;
		}
	mPaints.push_back(paint);
	return mPaints.size() - 1;
	}
	
int NanoVgCommandBuffer::addString (char const * string, char const * end) {
	if (!string) return -1;
	if (end) {
		NCBH_STRING str(string, end - string);
		mStrings.push_back(str);
		}
	else {
		NCBH_STRING str(string);
		mStrings.push_back(str);
		}
	return mStrings.size() - 1;
	}
		
void NanoVgCommandBuffer::swap (NanoVgCommandBuffer & other) {
	mCommands.swap(other.mCommands);
	mPaints.swap(other.mPaints);
	mStrings.swap(other.mStrings);
	}
	
void NanoVgCommandBuffer::clear () {
	mCommands.clear();
	mPaints.clear();
	mStrings.clear();
	}
		
void NanoVgCommandBuffer::dispatchSingle (NVGcontext * ctx, NanoVgCommandBuffer::command const & c) {
	switch (c.functionIdx) {
		// break
		// used to pause execution
		case NCB_Constants::NCB_pause:
			pauseCode = c.data.argsInts[0];
			instructionCounter = -1;
			return;
		
		// nvg composite
		case NCB_Constants::NCB_nvgGlobalCompositeOperation:
			return ::nvgGlobalCompositeOperation(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgGlobalCompositeBlendFunc:
			return ::nvgGlobalCompositeBlendFunc(ctx, c.data.argsInts[0], c.data.argsInts[1]);
		case NCB_Constants::NCB_nvgGlobalCompositeBlendFuncSeparate:
			return ::nvgGlobalCompositeBlendFuncSeparate(ctx, c.data.argsInts[0], c.data.argsInts[1], c.data.argsInts[2], c.data.argsInts[3]);
		
		// nvg state
		case NCB_Constants::NCB_nvgSave:
			return ::nvgSave(ctx);
		case NCB_Constants::NCB_nvgRestore:
			return ::nvgRestore(ctx);
		case NCB_Constants::NCB_nvgReset:
			return ::nvgReset(ctx);
		
		// nvg style
		case NCB_Constants::NCB_nvgShapeAntiAlias:
			return ::nvgShapeAntiAlias(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgStrokeColor:
			return ::nvgStrokeColor(ctx, nvgRGBAf(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]) );
		case NCB_Constants::NCB_nvgStrokePaint:
			return ::nvgStrokePaint(ctx, mPaints[c.data.argsInts[0]]);
		case NCB_Constants::NCB_nvgFillColor:
			return ::nvgFillColor(ctx, nvgRGBAf(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]) );
		case NCB_Constants::NCB_nvgFillPaint:
			return ::nvgFillPaint(ctx, mPaints[c.data.argsInts[0]]);
		case NCB_Constants::NCB_nvgMiterLimit:
			return ::nvgMiterLimit(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgStrokeWidth:
			return ::nvgStrokeWidth(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgLineCap:
			return ::nvgLineCap(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgLineJoin:
			return ::nvgLineJoin(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgGlobalAlpha:
			return ::nvgGlobalAlpha(ctx, c.data.argsFloats[0]);
	
		// nvg transform
		case NCB_Constants::NCB_nvgResetTransform:
			return ::nvgResetTransform(ctx);
		case NCB_Constants::NCB_nvgTransform:
			return ::nvgTransform(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsFloats[5]);
		case NCB_Constants::NCB_nvgTranslate:
			return ::nvgTranslate(ctx, c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgRotate:
			return ::nvgRotate(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgSkewX:
			return ::nvgSkewX(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgSkewY:
			return ::nvgSkewY(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgScale:
			return ::nvgScale(ctx, c.data.argsFloats[0], c.data.argsFloats[1]);
			
		// nvg scissor
		case NCB_Constants::NCB_nvgScissor:
			return ::nvgScissor(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgIntersectScissor:
			return ::nvgIntersectScissor(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgResetScissor:
			return ::nvgResetScissor(ctx);
			
		// nvg path
		case NCB_Constants::NCB_nvgBeginPath:
			return ::nvgBeginPath(ctx);
		case NCB_Constants::NCB_nvgMoveTo:
			return ::nvgMoveTo(ctx, c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgLineTo:
			return ::nvgLineTo(ctx, c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgBezierTo:
			return ::nvgBezierTo(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsFloats[5]);
		case NCB_Constants::NCB_nvgQuadTo:
			return ::nvgQuadTo(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgArcTo:
			return ::nvgArcTo(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4]);
		case NCB_Constants::NCB_nvgClosePath:
			return ::nvgClosePath(ctx);
			
		case NCB_Constants::NCB_nvgPathWinding:
			return ::nvgPathWinding(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgArc:
			return ::nvgArc(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsInts[5]);
		case NCB_Constants::NCB_nvgRect:
			return ::nvgRect(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgRoundedRect:
			return ::nvgRoundedRect(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4]);
		//case NCB_Constants::NCB_nvgRoundedRectVarying:
		//	abort(); // to many args, unused
		case NCB_Constants::NCB_nvgEllipse:
			return ::nvgEllipse(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgCircle:
			return ::nvgCircle(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2]);
		case NCB_Constants::NCB_nvgFill:
			return ::nvgFill(ctx);
		case NCB_Constants::NCB_nvgStroke:
			return ::nvgStroke(ctx);

		// text
		case NCB_Constants::NCB_nvgFontSize:
			return ::nvgFontSize(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgFontBlur:
			return ::nvgFontBlur(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgTextLetterSpacing:
			return ::nvgTextLetterSpacing(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgTextLineHeight:
			return ::nvgTextLineHeight(ctx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgTextAlign:
			return ::nvgTextLineHeight(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgFontFaceId:
			return ::nvgFontFaceId(ctx, c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgText:
			{
			const NCBH_STRING & str = c.data.argsInts[2] >= 0 ? mStrings[c.data.argsInts[2]].c_str() : NCBH_STRING("");
			return (void) ::nvgText(ctx, c.data.argsFloats[0], c.data.argsFloats[1], str.c_str(), NULL);
			}
		case NCB_Constants::NCB_nvgTextBox:
			{
			const NCBH_STRING & str = c.data.argsInts[3] >= 0 ? mStrings[c.data.argsInts[3]].c_str() : NCBH_STRING("");
			return (void) ::nvgTextBox(ctx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], str.c_str(), NULL);
			}
		
		#ifdef SDL_STB_PRODUCER_CONSUMER
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText:
			::nvgEndFrame(ctx);
			m_producer_consumer_font_cache->dispatchSingleText(c.data.argsInts[0]);
			return;
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerendered:
			::nvgEndFrame(ctx);
			m_producer_consumer_font_cache->dispatchSinglePrerendered(c.data.argsInts[0], c.data.argsInts[1], c.data.argsInts[2]);
			return;
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod:
			::nvgEndFrame(ctx);
			m_producer_consumer_font_cache->dispatchSinglePrerenderedWColorMod(c.data.argsInts[0], c.data.argsInts[1], c.data.argsInts[2], c.data.argsInts[3], c.data.argsInts[4], c.data.argsInts[5], c.data.argsInts[6]);
			return;
		#endif
		
		#ifdef BGFX
		case NCB_Constants::SSF_BGFX_SET_SCISSOR:
			((bgfx_stb_font_cache*) m_producer_consumer_font_cache->consumer_font_cache)->setScissor(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
			return;
		case NCB_Constants::SSF_BGFX_CLEAR_SCISSOR:
			((bgfx_stb_font_cache*) m_producer_consumer_font_cache->consumer_font_cache)->resetScissor();
			return;
		#endif
		
		default:
			{
			if (customCommandHandler)
				customCommandHandler->handleCustomCallback(this, ctx, c);
			//abort(); // unknown command
			}
			return;
		}
	}
		
#ifdef SDL_STB_PRODUCER_CONSUMER
// SDL_STB_PRODUCER_CONSUMER_Font functions to be used with producerConsumerFrontend
// https://github.com/SnapperTT/sdl_stb_font
void NanoVgCommandBuffer::pushSsfText(const int x, const int y, const NCBH_STRING & s, int* xOut, int * widthOut, int* heightOut) {
	pcfc_handle h = m_producer_consumer_font_cache->pushText(x, y, s, xOut, widthOut, heightOut);
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText, h, x, y));
	}
	
void NanoVgCommandBuffer::pushSsfText(const int x, const int y, const sttfont_formatted_text & s, int* xOut, int * widthOut, int* heightOut) {
	pcfc_handle h = m_producer_consumer_font_cache->pushText(x, y, s, xOut, widthOut, heightOut);
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText, h, x, y));
	}
	
void NanoVgCommandBuffer::pushSsfText(const int x, const int y, const char* c, int* xOut, int * widthOut, int* heightOut) {
	pcfc_handle h = m_producer_consumer_font_cache->pushText(x, y, c, -1, xOut, widthOut, heightOut);
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText, h, x, y));
	}
	
void NanoVgCommandBuffer::pushSsfText(const int x, const int y, const sttfont_format & format, const NCBH_STRING & s, int* xOut, int * widthOut, int* heightOut) {
	pcfc_handle h = m_producer_consumer_font_cache->pushText(x, y, format, s, xOut, widthOut, heightOut);
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText, h, x, y));
	}
	
void NanoVgCommandBuffer::pushSsfText(const int x, const int y, const sttfont_format & format, const char* c, int* xOut, int * widthOut, int* heightOut) {
	pcfc_handle h = m_producer_consumer_font_cache->pushText(x, y, format, c, -1, xOut, widthOut, heightOut);
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText, h, x, y));
	}
	
void NanoVgCommandBuffer::pushSsfPrerendered(const int textHandle, const int x, const int y) {
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerendered, textHandle, x, y));
	}
	
void NanoVgCommandBuffer::pushSsfPrerenderedWColorMod(const int textHandle, const int x, const int y, const int r, const int g, const int b, const int a) {
	mCommands.push_back(command(NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod, textHandle, x, y, r, g, b, a));
	}
#endif

void NanoVgCommandBuffer::dispatch (NVGcontext * ctx) {
	int sz = mCommands.size();
	
	#if NCBH_PAGEQUEUE_RANDOM_ACCESS 
		auto itt = mCommands.begin() + instructionCounter;
	#else
		auto itt = mCommands.iter_at(instructionCounter);
	#endif
	
	for (int i = instructionCounter; i < sz; ++i, ++itt) {
		dispatchSingle(ctx, *itt);
		
		// pause rendering until called again
		if (instructionCounter < 0) {
			instructionCounter = i+1;
			return;
			}
		}
	
	// reset instruction counter on completion so that the user can re-dispatch if they wish
	instructionCounter = 0;
	}


void NanoVgCommandBuffer::sttr_register() {
	#ifdef STTR_CLASS_SIG
	// see snappertt/sttr on github
	#define STTR_NVG_METH(C, X, MFLAGS) regField<C,decltype(&C::X),MFLAGS>(&C::X, #X).setUserFlags(MFLAGS)
	#define STTR_NVG_PROP(C, X, MFLAGS) regField<C,decltype(&C::X),MFLAGS>(&C::X, #X).setUserFlags(MFLAGS)
	
	sttr::RegNamespace & R = *sttr::getGlobalNamespace();
	R.beginClass<NVGcontext>("NVGcontext")
	.endClass();
	R.beginClass<nvgw>("nvgw")
		.STTR_NVG_METH(nvgw, nvgLinearGradient, 0)
		.STTR_NVG_METH(nvgw, nvgBoxGradient, 0)
		.STTR_NVG_METH(nvgw, nvgRadialGradient, 0)
		
		.STTR_NVG_METH(nvgw, nvgRGB, 0)
		.STTR_NVG_METH(nvgw, nvgRGBf, 0)
		.STTR_NVG_METH(nvgw, nvgRGBA, 0)
		.STTR_NVG_METH(nvgw, nvgRGBAf, 0)
		.STTR_NVG_METH(nvgw, nvgLerpRGBA, 0)
		.STTR_NVG_METH(nvgw, nvgTransRGBA, 0)
		.STTR_NVG_METH(nvgw, nvgTransRGBAf, 0)
		.STTR_NVG_METH(nvgw, nvgHSL, 0)
		.STTR_NVG_METH(nvgw, nvgHSLA, 0)
	.endClass();
	R.beginClass<NVGcolor>("NVGcolor")
		.STTR_NVG_PROP(NVGcolor, rgba, 0)
		.STTR_NVG_PROP(NVGcolor, r, 0)
		.STTR_NVG_PROP(NVGcolor, g, 0)
		.STTR_NVG_PROP(NVGcolor, b, 0)
		.STTR_NVG_PROP(NVGcolor, a, 0)
	.endClass();
	R.beginClass<NVGpaint>("NVGpaint")
		.STTR_NVG_PROP(NVGpaint, xform, 0)
		.STTR_NVG_PROP(NVGpaint, extent, 0)
		.STTR_NVG_PROP(NVGpaint, radius, 0)
		.STTR_NVG_PROP(NVGpaint, feather, 0)
		.STTR_NVG_PROP(NVGpaint, innerColor, 0)
		.STTR_NVG_PROP(NVGpaint, outerColor, 0)
	.endClass();
	R.beginClass<NanoVgCommandBuffer>("NanoVgCommandBuffer")
		.STTR_NVG_METH(NanoVgCommandBuffer, pause, 0)
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgGlobalCompositeOperation, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgGlobalCompositeBlendFunc, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgGlobalCompositeBlendFuncSeparate, 0)
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgSave, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgRestore, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgReset, 0)
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgShapeAntiAlias, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgStrokeColor, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgStrokePaint, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgFillColor, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgFillPaint, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgMiterLimit, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgStrokeWidth, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgLineCap, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgLineJoin, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgGlobalAlpha, 0)
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgResetTransform, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgTransform, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgTranslate, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgRotate, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgSkewX, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgSkewY, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgScale, 0)
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgScissor, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgIntersectScissor, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgResetScissor, 0)
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgBeginPath, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgMoveTo, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgLineTo, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgBezierTo, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgQuadTo, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgArcTo, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgClosePath, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgPathWinding, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgArc, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgRect, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgRoundedRect, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgEllipse, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgCircle, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgFill, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgStroke, 0)
		// text not supported
	.endClass();
	#undef STTR_NVG_METH
	#undef STTR_NVG_PROP
	#endif // STTR
	}
#endif
