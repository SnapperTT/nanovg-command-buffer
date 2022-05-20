#ifndef NANOVG_COMMAND_BUFFER_HPP
#define NANOVG_COMMAND_BUFFER_HPP

#include <cstdint>
#include <vector>
#include <string>

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
		inline explicit command (const int32_t _id, const float f0, const float f1, const int i2) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsInts[2] = i2; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const int i3) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsInts[3] = i3; }
	};
	std::vector <NanoVgCommandBuffer::command> mCommands;
	std::vector <NVGpaint> mPaints;
	std::vector <std::string> mStrings;
protected:
	int addPaint (NVGpaint const & paint);
	int addString (char const * string, char const * end);
public:
	void swap (NanoVgCommandBuffer & other);
	void clear ();
	void dispatchSingle (NVGcontext * const ctx, NanoVgCommandBuffer::command const & c);
	void dispatchAll (NVGcontext * const ctx);

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
		mCommands.push_back(command(NCB_Constants::NCB_nvgStrokePaint, idx));
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

	};
#endif

#ifdef NANOVG_COMMAND_BUFFER_IMPL
#ifndef NANOVG_COMMAND_BUFFER_GLOBAL_CONTEXT
	#define NCB_CTX ctx, 
	#define NCB_CTXNC ctx
#endif

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
		std::string str(string, end - string);
		mStrings.push_back(str);
		}
	else {
		std::string str(string);
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
		
void NanoVgCommandBuffer::dispatchSingle (NVGcontext * const ctx, NanoVgCommandBuffer::command const & c) {
	switch (c.functionIdx) {
		// nvg composite
		case NCB_Constants::NCB_nvgGlobalCompositeOperation:
			return nvgGlobalCompositeOperation(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgGlobalCompositeBlendFunc:
			return nvgGlobalCompositeBlendFunc(NCB_CTX c.data.argsInts[0], c.data.argsInts[1]);
		case NCB_Constants::NCB_nvgGlobalCompositeBlendFuncSeparate:
			return nvgGlobalCompositeBlendFuncSeparate(NCB_CTX c.data.argsInts[0], c.data.argsInts[1], c.data.argsInts[2], c.data.argsInts[3]);
		
		// nvg state
		case NCB_Constants::NCB_nvgSave:
			return nvgSave(NCB_CTXNC);
		case NCB_Constants::NCB_nvgRestore:
			return nvgRestore(NCB_CTXNC);
		case NCB_Constants::NCB_nvgReset:
			return nvgReset(NCB_CTXNC);
		
		// nvg style
		case NCB_Constants::NCB_nvgShapeAntiAlias:
			return nvgShapeAntiAlias(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgStrokeColor:
			return nvgStrokeColor(NCB_CTX nvgRGBAf(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]) );
		case NCB_Constants::NCB_nvgStrokePaint:
			return nvgStrokePaint(NCB_CTX mPaints[c.data.argsInts[0]]);
		case NCB_Constants::NCB_nvgFillColor:
			return nvgFillColor(NCB_CTX nvgRGBAf(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]) );
		case NCB_Constants::NCB_nvgFillPaint:
			return nvgFillPaint(NCB_CTX mPaints[c.data.argsInts[0]]);
		case NCB_Constants::NCB_nvgMiterLimit:
			return nvgMiterLimit(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgStrokeWidth:
			return nvgStrokeWidth(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgLineCap:
			return nvgLineCap(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgLineJoin:
			return nvgLineJoin(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgGlobalAlpha:
			return nvgGlobalAlpha(NCB_CTX c.data.argsFloats[0]);
	
		// nvg transform
		case NCB_Constants::NCB_nvgResetTransform:
			return nvgResetTransform(NCB_CTXNC);
		case NCB_Constants::NCB_nvgTransform:
			return nvgTransform(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsFloats[5]);
		case NCB_Constants::NCB_nvgTranslate:
			return nvgTranslate(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgRotate:
			return nvgRotate(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgSkewX:
			return nvgSkewX(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgSkewY:
			return nvgSkewY(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgScale:
			return nvgScale(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1]);
			
		// nvg scissor
		case NCB_Constants::NCB_nvgScissor:
			return nvgScissor(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgIntersectScissor:
			return nvgIntersectScissor(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgResetScissor:
			return nvgResetScissor(NCB_CTXNC);
			
		// nvg path
		case NCB_Constants::NCB_nvgBeginPath:
			return nvgBeginPath(NCB_CTXNC);
		case NCB_Constants::NCB_nvgMoveTo:
			return nvgMoveTo(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgLineTo:
			return nvgLineTo(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgBezierTo:
			return nvgBezierTo(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsFloats[5]);
		case NCB_Constants::NCB_nvgQuadTo:
			return nvgQuadTo(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgArcTo:
			return nvgArcTo(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4]);
		case NCB_Constants::NCB_nvgClosePath:
			return nvgClosePath(NCB_CTXNC);
			
		case NCB_Constants::NCB_nvgPathWinding:
			return nvgPathWinding(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgArc:
			return nvgArc(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsInts[5]);
		case NCB_Constants::NCB_nvgRect:
			return nvgRect(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgRoundedRect:
			return nvgRoundedRect(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4]);
		//case NCB_Constants::NCB_nvgRoundedRectVarying:
		//	abort(); // to many args, unused
		case NCB_Constants::NCB_nvgEllipse:
			return nvgEllipse(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgCircle:
			return nvgCircle(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2]);
		case NCB_Constants::NCB_nvgFill:
			return nvgFill(NCB_CTXNC);
		case NCB_Constants::NCB_nvgStroke:
			return nvgStroke(NCB_CTXNC);

		// text
		case NCB_Constants::NCB_nvgFontSize:
			return nvgFontSize(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgFontBlur:
			return nvgFontBlur(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgTextLetterSpacing:
			return nvgTextLetterSpacing(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgTextLineHeight:
			return nvgTextLineHeight(NCB_CTX c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgTextAlign:
			return nvgTextLineHeight(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgFontFaceId:
			return nvgFontFaceId(NCB_CTX c.data.argsInts[0]);
		case NCB_Constants::NCB_nvgText:
			{
			const std::string & str = c.data.argsInts[2] >= 0 ? mStrings[c.data.argsInts[2]].c_str() : std::string("");
			return (void) nvgText(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], str.c_str(), NULL);
			}
		case NCB_Constants::NCB_nvgTextBox:
			{
			const std::string & str = c.data.argsInts[3] >= 0 ? mStrings[c.data.argsInts[3]].c_str() : std::string("");
			return (void) nvgTextBox(NCB_CTX c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], str.c_str(), NULL);
			}
		default:
			//abort(); // unknown command
		}
	}
		
void NanoVgCommandBuffer::dispatchAll (NVGcontext * const ctx) {
	for (const command & c : mCommands)
		dispatchSingle(ctx, c);
	}
#endif
