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

#ifndef NCBH_BACKEND_IS_VG_RENDERER
	#define NCBH_BACKEND_IS_VG_RENDERER 1
#endif

#ifndef NANOVG_BACKEND
	#define NANOVG_BACKEND 1
#endif
#ifndef VGRENDERER_BACKEND
	#define VGRENDERER_BACKEND 0
#endif
#ifndef NCBH_ABORT
	#define NCBH_ABORT abort();
#endif

struct sttfont_formatted_text;
struct sttfont_format;
class NanoVgCommandBufferCustomCallbackI;

namespace vg {
	struct Context;
	struct GradientHandle;
	}
struct NVGcontext;

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
	
	// gradiant
	static constexpr int32_t NCB_nvgLinearGradient = 50;
	static constexpr int32_t NCB_nvgBoxGradient = 51;
	static constexpr int32_t NCB_nvgRadialGradient = 52;
	
	// break
	static constexpr int32_t NCB_pause = 1000;
	
	// sdlStbFont Stuff
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawText = 1001;
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawPrerendered = 1002;
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod = 1003;
	static constexpr int32_t SDL_STB_PRODUCER_CONSUMER_drawTextDirectly = 1004;
	static constexpr int32_t SSF_BGFX_SET_SCISSOR = 1004;
	static constexpr int32_t SSF_BGFX_CLEAR_SCISSOR = 1005;
	
	// custom engine stuff
	};

struct NCBColor {
	float r,g,b,a;
	inline NCBColor() {}
	inline NCBColor(const float _r, const float _g, const float _b, const float _a) : r(_r), g(_g), b(_b), a(_a) {}
		
	#if NANOVG_BACKEND
	inline NVGcolor toNVGcolor() const {
		return ::nvgRGBAf(r,g,b,a);
		}
	#endif // NANOVG_BACKEND
	#if VGRENDERER_BACKEND
	inline vg::Color toVgColor() const {
		return vg::color4f(r,g,b,a);
		}
	#endif // NANOVG_BACKEND
	};
	
struct NCBGradientGenerator {
	static constexpr int MODE_LINEAR_GRADIENT = 1;
	static constexpr int MODE_BOX_GRADIENT = 2;
	static constexpr int MODE_RADIAL_GRADIENT = 3;
	int type;
	float params[6];
	NCBColor icol;
	NCBColor ocol;
	};

struct nvgw {
	// For sttr registering with a namespace
	inline static NCBColor nvgRGB(unsigned char r, unsigned char g, unsigned char b) {
		return NCBColor(r/255.0,g/255.0,b/255.0,1.0f);
		}
	inline static NCBColor nvgRGBf(float r, float g, float b) {
		return NCBColor(r, g, b, 1.0);
		}
	inline static NCBColor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		return NCBColor(r/255.0, g/255.0, b/255.0, a/255.0);
		}
	inline static NCBColor nvgRGBAf(float r, float g, float b, float a) {
		return NCBColor(r, g, b, a);
		}
	inline static NCBColor nvgLerpRGBA(const NCBColor& c0, const NCBColor& c1, float u) {
		const float um = 1.0f - u;
		return NCBColor(c0.r*um + c1.r*u, c0.g*um + c1.g*u, c0.b*um + c1.b*u, c0.a*um + c1.a*u);
		}
	inline static NCBColor nvgTransRGBA(const NCBColor& c0, unsigned char a) {
		return NCBColor(c0.r, c0.g, c0.b, a/255.0);
		}
	inline static NCBColor nvgTransRGBAf(const NCBColor& c0, float a) {
		return NCBColor(c0.r, c0.g, c0.b, a);
		}
	
	static NCBColor nvgHSLA_worker(float h, float s, float l, unsigned char a);
	
	inline static NCBColor nvgHSLA(float h, float s, float l, unsigned char a) {
		return nvgHSLA_worker(h, s, l, a);
		}
	inline static NCBColor nvgHSL(float h, float s, float l) {
		return nvgHSLA_worker(h, s, l, 255);
		}
		
	#if VGRENDERER_BACKEND
	// no AA
	static constexpr uint32_t VgStrokeFlag_ButtMiter   = vg::StrokeFlags::ButtMiter;
	static constexpr uint32_t VgStrokeFlag_ButtRound   = vg::StrokeFlags::ButtRound;
	static constexpr uint32_t VgStrokeFlag_ButtBevel   = vg::StrokeFlags::ButtBevel;
	static constexpr uint32_t VgStrokeFlag_RoundMiter  = vg::StrokeFlags::RoundMiter;
	static constexpr uint32_t VgStrokeFlag_RoundRound  = vg::StrokeFlags::RoundRound;
	static constexpr uint32_t VgStrokeFlag_RoundBevel  = vg::StrokeFlags::RoundBevel;
	static constexpr uint32_t VgStrokeFlag_SquareMiter = vg::StrokeFlags::SquareMiter;
	static constexpr uint32_t VgStrokeFlag_SquareRound = vg::StrokeFlags::SquareRound;
	static constexpr uint32_t VgStrokeFlag_SquareBevel = vg::StrokeFlags::SquareBevel;
	// w/ AA
	static constexpr uint32_t VgStrokeFlag_ButtMiterAA   = vg::StrokeFlags::ButtMiterAA;
	static constexpr uint32_t VgStrokeFlag_ButtRoundAA   = vg::StrokeFlags::ButtRoundAA;
	static constexpr uint32_t VgStrokeFlag_ButtBevelAA   = vg::StrokeFlags::ButtBevelAA;
	static constexpr uint32_t VgStrokeFlag_RoundMiterAA  = vg::StrokeFlags::RoundMiterAA;
	static constexpr uint32_t VgStrokeFlag_RoundRoundAA  = vg::StrokeFlags::RoundRoundAA;
	static constexpr uint32_t VgStrokeFlag_RoundBevelAA  = vg::StrokeFlags::RoundBevelAA;
	static constexpr uint32_t VgStrokeFlag_SquareMiterAA = vg::StrokeFlags::SquareMiterAA;
	static constexpr uint32_t VgStrokeFlag_SquareRoundAA = vg::StrokeFlags::SquareRoundAA;
	static constexpr uint32_t VgStrokeFlag_SquareBevelAA = vg::StrokeFlags::SquareBevelAA;
	#endif
	};
	
struct ncb_error_handler {
	static void error(const char * msg) {
		NCBH_ABORT;
		}
	static void not_found(const char* msg) {
		NCBH_ABORT;
		}
	};

class NanoVgCommandBuffer {
public:
	struct dispatchState {
		int32_t lastCommandId;
		int32_t nextCommandId;
		int activePaintOrGradiantId; // -1 = disabled
		NCBColor activeColour;
		
		inline void initToZero() {
			lastCommandId = NCB_Constants::NCB_unknown;;
			nextCommandId = NCB_Constants::NCB_unknown;;
			activePaintOrGradiantId = -1;
			activeColour = NCBColor(1.f, 1.f, 1.f, 1.f);
			}
		};
	
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
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const float f3, const int i4) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsFloats[3] = f3; data.argsInts[4] = i4; }
		inline explicit command (const int32_t _id, const int i0) : functionIdx(_id) { data.argsInts[0] = i0; }
		inline explicit command (const int32_t _id, const int i0, const float f1, const int i2) : functionIdx(_id) { data.argsInts[0] = i0; data.argsFloats[1] = f1; data.argsInts[2] = i2; }
		inline explicit command (const int32_t _id, const int i0, const int i1) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3, const int i4) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; data.argsInts[4] = i4; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3, const int i4, const int i5) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; data.argsInts[4] = i4; data.argsInts[5] = i5; }
		inline explicit command (const int32_t _id, const int i0, const int i1, const int i2, const int i3, const int i4, const int i5, const int i6) : functionIdx(_id) { data.argsInts[0] = i0; data.argsInts[1] = i1; data.argsInts[2] = i2; data.argsInts[3] = i3; data.argsInts[4] = i4; data.argsInts[5] = i5; data.argsInts[6] = i6; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const int i2) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsInts[2] = i2; }
		inline explicit command (const int32_t _id, const float f0, const float f1, const float f2, const int i3) : functionIdx(_id) { data.argsFloats[0] = f0; data.argsFloats[1] = f1; data.argsFloats[2] = f2; data.argsInts[3] = i3; }
	};
	// TBD - with std-stll integration supply a disposable bump allocator instead of this stuff
	// this is not really a hotspot for allocations - its just a few reallocs per frame
	NCBH_PAGEQUEUE <NanoVgCommandBuffer::command> mCommands;
	NCBH_VECTOR <NCBGradientGenerator> mGradientGenerators;
	NCBH_VECTOR <NCBH_STRING> mStrings;
	
	#if VGRENDERER_BACKEND
		NCBH_VECTOR <vg::GradientHandle> mGradients;
	#endif
	#if NANOVG_BACKEND
		NCBH_VECTOR <NVGpaint> mPaints;
	#endif
	
	#ifdef SDL_STB_PRODUCER_CONSUMER
	producer_consumer_font_cache* m_producer_consumer_font_cache;
	#endif
	NanoVgCommandBufferCustomCallbackI* customCommandHandler;
	int pauseCode;
	int instructionCounter;
		
protected:
	int addPaintGenerator (NCBGradientGenerator const & paint);
	int addString (char const * string, char const * end);
public:
	NanoVgCommandBuffer();
	void swap (NanoVgCommandBuffer & other);
	void clear ();
	void dispatchSingle (NVGcontext * ctx, vg::Context * vgCtx, NanoVgCommandBuffer::command const & c, NanoVgCommandBuffer::dispatchState & mDispatchSide);
	inline void dispatchSingle (NVGcontext * ctx, vg::Context * vgCtx, NanoVgCommandBuffer::command const & c) { dispatchState s; s.initToZero(); dispatchSingle(ctx, vgCtx, c, s); }
	void dispatch (NVGcontext * ctx);
	void dispatchVg (vg::Context * ctx);
protected:
	void dispatch_worker (NVGcontext * ctx, vg::Context * vgCtx);
public:
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
	inline void nvgStrokeColor(const NCBColor& color, const float vgLineWidth, const int vgStrokeFlags) {
		// note that vg* only has effect with vgrenderer backend
		mCommands.push_back(command(NCB_Constants::NCB_nvgStrokeColor, color.r, color.g, color.b, color.a, vgLineWidth, vgStrokeFlags));
		}
	inline void nvgStrokePaint(int paintIdx, const float vgLineWidth, const int vgStrokeFlags) {
		// note that vg* only has effect with vgrenderer backend
		mCommands.push_back(command(NCB_Constants::NCB_nvgStrokePaint, paintIdx, vgLineWidth, vgStrokeFlags));
		}
	//inline void nvgStrokePaint(const NCBGradientGenerator & constructionInfo) {
	//	int idx = addPaintGenerator(constructionInfo);
	//	mCommands.push_back(command(NCB_Constants::NCB_nvgStrokePaint, idx));
	//	}
	inline void nvgFillColor(const NCBColor& color) {
		int useAa = 1;
		int flags = 0;
		#if VGRENDERER_BACKEND
			flags = useAa ? vg::FillFlags::ConvexAA :  vg::FillFlags::Convex;
		#endif
		mCommands.push_back(command(NCB_Constants::NCB_nvgFillColor, color.r, color.g, color.b, color.a, flags));
		}
	//inline void nvgFillPaint(const NCBGradientGenerator & constructionInfo) {
	//	int idx = addPaintGenerator(constructionInfo);
	//	mCommands.push_back(command(NCB_Constants::NCB_nvgFillPaint, idx));
	//	}
	inline void nvgFillPaint(int paintIdx) {
		int useAa = 1;
		int flags = 0;
		#if VGRENDERER_BACKEND
			flags = useAa ? vg::FillFlags::ConvexAA :  vg::FillFlags::Convex;
		#endif
		mCommands.push_back(command(NCB_Constants::NCB_nvgFillPaint, paintIdx, flags));
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
	
	int nvgLinearGradient(float sx, float sy, float ex, float ey, const NCBColor& icol, const NCBColor& ocol);

	int nvgBoxGradient(float x, float y, float w, float h, float r, float f, const NCBColor& icol, const NCBColor& ocol);
		
	int nvgRadialGradient(float cx, float cy, float inr, float outr, const NCBColor& icol, const NCBColor& ocol);
	
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
	virtual inline bool handleCustomCallback(NanoVgCommandBuffer * NVG, NVGcontext * ctx, vg::Context * vgCtx, NanoVgCommandBuffer::command const & c) {
		return true;
		}
	};
	

#ifdef SDL_STB_PRODUCER_CONSUMER
#if VGRENDERER_BACKEND
struct VgRendererSSFCustomCallbackWrapper {
	struct textCallback {
		producer_consumer_font_cache* m_producer_consumer_font_cache;
		int commandId;
		int lastCommandId;
		int nextCommandId;
		int textId;
		int x,y;
		uint8_t r,g,b,a;
		};
	static void vgCustomCallback(vg::Context* ctx, void* usrPtr, const uint32_t a, const uint32_t b);
	};
#endif // VGRENDERER_BACKEND
#endif // SDL_STB_PRODUCER_CONSUMER
	
#endif

#ifdef NANOVG_COMMAND_BUFFER_IMPL
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start Implementation

NCBColor nvgw::nvgHSLA_worker(float h, float s, float l, unsigned char a) {
	float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s; // Chroma
	float x = c * (1.0f - fabsf(fmodf(h * 6.0f, 2.0f) - 1.0f));
	float m = l - c / 2.0f;

	float r1, g1, b1;
	if (h < 1.0f / 6.0f)      { r1 = c; g1 = x; b1 = 0; }
	else if (h < 2.0f / 6.0f) { r1 = x; g1 = c; b1 = 0; }
	else if (h < 3.0f / 6.0f) { r1 = 0; g1 = c; b1 = x; }
	else if (h < 4.0f / 6.0f) { r1 = 0; g1 = x; b1 = c; }
	else if (h < 5.0f / 6.0f) { r1 = x; g1 = 0; b1 = c; }
	else                      { r1 = c; g1 = 0; b1 = x; }
	return NCBColor(r1+m, g1+m, b1+m, a/255.0);
	}
	
#ifdef SDL_STB_PRODUCER_CONSUMER
#if VGRENDERER_BACKEND
void VgRendererSSFCustomCallbackWrapper::vgCustomCallback(vg::Context* ctx, void* usrPtr, const uint32_t a, const uint32_t b) {
	textCallback& cb = *((textCallback*) usrPtr);
	switch (cb.commandId) {
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText:
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawTextDirectly:
			{
			if (cb.lastCommandId != NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText
				&& cb.lastCommandId != NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawTextDirectly) {
				cb.m_producer_consumer_font_cache->consumer_font_cache->onStartDrawing(); // start batched text rendering
				}
				
			if (cb.commandId == NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText)
				cb.m_producer_consumer_font_cache->dispatchSingleText(cb.textId);
			else
				cb.m_producer_consumer_font_cache->consumer_font_cache->drawText(cb.x, cb.y, "direct");
			
			if (cb.lastCommandId != NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText
				&& cb.lastCommandId != NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawTextDirectly) {
				cb.m_producer_consumer_font_cache->consumer_font_cache->onCompletedDrawing(); // finish batched text rendering
				}
			}
			return;
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerendered:
			cb.m_producer_consumer_font_cache->dispatchSinglePrerendered(cb.textId, cb.x, cb.y);
			return;
		case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod:
			cb.m_producer_consumer_font_cache->dispatchSinglePrerenderedWColorMod(cb.textId, cb.x, cb.y, cb.r, cb.g, cb.b, cb.a);
			return;
		}
	}
#endif // VGRENDERER_BACKEND
#endif // SDL_STB_PRODUCER_CONSUMER

NanoVgCommandBuffer::NanoVgCommandBuffer() {
	#ifdef SDL_STB_PRODUCER_CONSUMER
		m_producer_consumer_font_cache = NULL;
	#endif
	
	pauseCode = 0;
	instructionCounter = 0;
	customCommandHandler = NULL;
	}
	
int NanoVgCommandBuffer::addPaintGenerator (NCBGradientGenerator const & paint) {
	if (mGradientGenerators.size()) {
		// easy out - resusue paint if its the same as previous
		int sz = mGradientGenerators.size();
		int iBegin = sz - 8; // check the last X paints so that we're not creating duplicates
		if (iBegin < 0) iBegin = 0;
		for (int i = iBegin; i < sz; ++i)
			if (memcmp(&mGradientGenerators[i], &paint, sizeof(NCBGradientGenerator)) == 0)
				return i;
		}
	mGradientGenerators.push_back(paint);
	return mGradientGenerators.size() - 1;
	}
	
int NanoVgCommandBuffer::addString (char const * string, char const * end) {
	if (!string) return -1;
	
	int sz = mStrings.size();
	int iBegin = sz - 8;
	if (iBegin < 0) iBegin = 0;
		
	if (end) {
		NCBH_STRING str(string, end - string);
		for (int i = iBegin; i < sz; ++i)
			if (mStrings[i] == str) return i;
		mStrings.push_back(str);
		}
	else {
		NCBH_STRING str(string);
		for (int i = iBegin; i < sz; ++i)
			if (mStrings[i] == str) return i;
		mStrings.push_back(str);
		}
	return mStrings.size() - 1;
	}
		
void NanoVgCommandBuffer::swap (NanoVgCommandBuffer & other) {
	mCommands.swap(other.mCommands);
	mGradientGenerators.swap(other.mGradientGenerators);
	mStrings.swap(other.mStrings);
	#if VGRENDERER_BACKEND
		mGradients.swap(other.mGradients);
	#endif
	#if NANOVG_BACKEND
		mPaints.swap(other.mPaints);
	#endif
	}
	
void NanoVgCommandBuffer::clear () {
	mCommands.clear();
	mGradientGenerators.clear();
	mStrings.clear();
	#if VGRENDERER_BACKEND
		mGradients.clear();
	#endif
	#if NANOVG_BACKEND
		mPaints.clear();
	#endif
	}
	
void NanoVgCommandBuffer::dispatchSingle (NVGcontext * ctx, vg::Context * vgCtx, NanoVgCommandBuffer::command const & c, NanoVgCommandBuffer::dispatchState & mDispatchSide) {
	switch (c.functionIdx) {
		// break
		// used to pause execution
		case NCB_Constants::NCB_pause:
			pauseCode = c.data.argsInts[0];
			instructionCounter = -1;
			return;
		
		// nvg composite
		#if NANOVG_BACKEND
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
		
		// gradiants
		case NCB_Constants::NCB_nvgLinearGradient:
			{
			unsigned int idx = c.data.argsInts[0];
			if (idx < mGradientGenerators.size())
				return ncb_error_handler::error("mGradientGenerators array index out of range");
			NCBGradientGenerator & G = mGradientGenerators[idx];
			NVGpaint GH = ::nvgLinearGradient(ctx, G.params[0], G.params[1], G.params[2], G.params[3], G.icol.toNVGcolor(), G.ocol.toNVGcolor());
			mPaints[idx] = GH;
			mDispatchSide.activePaintOrGradiantId = idx;
			}
			return;
			
		case NCB_Constants::NCB_nvgBoxGradient:
			{
			unsigned int idx = c.data.argsInts[0];
			if (idx < mGradientGenerators.size())
				return ncb_error_handler::error("mGradientGenerators array index out of range");
			NCBGradientGenerator & G = mGradientGenerators[idx];
			NVGpaint GH = ::nvgBoxGradient(ctx, G.params[0], G.params[1], G.params[2], G.params[3], G.params[4], G.params[5], G.icol.toNVGcolor(), G.ocol.toNVGcolor());
			mPaints[idx] = GH;
			mDispatchSide.activePaintOrGradiantId = idx;
			}
			return;
			
		case NCB_Constants::NCB_nvgRadialGradient:
			{
			unsigned int idx = c.data.argsInts[0];
			if (idx < mGradientGenerators.size())
				return ncb_error_handler::error("mGradientGenerators array index out of range");
			NCBGradientGenerator & G = mGradientGenerators[idx];
			NVGpaint GH = ::nvgRadialGradient(ctx, G.params[0], G.params[1], G.params[2], G.params[3], G.icol.toNVGcolor(), G.ocol.toNVGcolor());
			mPaints[idx] = GH;
			mDispatchSide.activePaintOrGradiantId = idx;
			}
			return;
		
			#ifdef SDL_STB_PRODUCER_CONSUMER
				case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText:
					if (mDispatchSide.lastCommandId != NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText) {
						::nvgEndFrame(ctx);
						m_producer_consumer_font_cache->consumer_font_cache->onStartDrawing(); // start batched text rendering
						}
					
					m_producer_consumer_font_cache->dispatchSingleText(c.data.argsInts[0]);
					
					if (mDispatchSide.nextCommandId != NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText) {
						m_producer_consumer_font_cache->consumer_font_cache->onCompletedDrawing(); // finish and draw the batch
						}
					return;
				case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerendered:
					::nvgEndFrame(ctx);
					m_producer_consumer_font_cache->dispatchSinglePrerendered(c.data.argsInts[0], c.data.argsInts[1], c.data.argsInts[2]);
					return;
				case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod:
					::nvgEndFrame(ctx);
					m_producer_consumer_font_cache->dispatchSinglePrerenderedWColorMod(c.data.argsInts[0], c.data.argsInts[1], c.data.argsInts[2], c.data.argsInts[3], c.data.argsInts[4], c.data.argsInts[5], c.data.argsInts[6]);
					return;
			#endif	//SDL_STB_PRODUCER_CONSUMER
		#endif // NANOVG_BACKEND
		#if VGRENDERER_BACKEND
		case NCB_Constants::NCB_nvgGlobalCompositeOperation:
			return ncb_error_handler::not_found("NCB_nvgGlobalCompositeOperation not defined for vg-renderer");
		case NCB_Constants::NCB_nvgGlobalCompositeBlendFunc:
			return ncb_error_handler::not_found("NCB_nvgGlobalCompositeBlendFunc not defined for vg-renderer");
		case NCB_Constants::NCB_nvgGlobalCompositeBlendFuncSeparate:
			return ncb_error_handler::not_found("NCB_nvgGlobalCompositeBlendFuncSeparate not defined for vg-renderer");
		
		// nvg state
		case NCB_Constants::NCB_nvgSave:
			return vg::pushState(vgCtx);
		case NCB_Constants::NCB_nvgRestore:
			return vg::popState(vgCtx);
		case NCB_Constants::NCB_nvgReset:
			return ncb_error_handler::not_found("NCB_nvgReset not defined for vg-renderer");
		
		// nvg style
		case NCB_Constants::NCB_nvgShapeAntiAlias:
			return ncb_error_handler::not_found("NCB_nvgShapeAntiAlias not defined for vg-renderer");
		case NCB_Constants::NCB_nvgStrokeColor:
			return vg::strokePath(vgCtx, vg::color4f(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]), c.data.argsFloats[4], c.data.argsInts[5]);
		case NCB_Constants::NCB_nvgStrokePaint:
			return vg::strokePath(vgCtx, mGradients[c.data.argsInts[0]], c.data.argsFloats[1], c.data.argsInts[2]);
		case NCB_Constants::NCB_nvgFillColor:
			return vg::fillPath(vgCtx, vg::color4f(c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]), c.data.argsInts[4] );
		case NCB_Constants::NCB_nvgFillPaint:
			return vg::fillPath(vgCtx, mGradients[c.data.argsInts[0]], c.data.argsInts[1]);
		case NCB_Constants::NCB_nvgMiterLimit:
			return ncb_error_handler::not_found("NCB_nvgMiterLimit not defined for vg-renderer");
		case NCB_Constants::NCB_nvgStrokeWidth:
			return ncb_error_handler::not_found("NCB_nvgStrokeWidth not defined for vg-renderer");
		case NCB_Constants::NCB_nvgLineCap:
			return ncb_error_handler::not_found("NCB_nvgLineCap not defined for vg-renderer");
		case NCB_Constants::NCB_nvgLineJoin:
			return ncb_error_handler::not_found("NCB_nvgLineJoin not defined for vg-renderer");
		case NCB_Constants::NCB_nvgGlobalAlpha:
			return vg::setGlobalAlpha(vgCtx, c.data.argsFloats[0]);
	
		// nvg transform
		case NCB_Constants::NCB_nvgResetTransform:
			return vg::transformIdentity(vgCtx);
		case NCB_Constants::NCB_nvgTransform:
			return vg::transformMult(vgCtx, &c.data.argsFloats[0] , vg::TransformOrder::Pre);
		case NCB_Constants::NCB_nvgTranslate:
			return vg::transformTranslate(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgRotate:
			return vg::transformRotate(vgCtx, c.data.argsFloats[0]);
		case NCB_Constants::NCB_nvgSkewX:
			return ncb_error_handler::not_found("NCB_nvgSkewX not defined for vg-renderer");
		case NCB_Constants::NCB_nvgSkewY:
			return ncb_error_handler::not_found("NCB_nvgSkewY not defined for vg-renderer");
		case NCB_Constants::NCB_nvgScale:
			return vg::transformScale(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1]);
			
		// nvg scissor
		case NCB_Constants::NCB_nvgScissor:
			return vg::setScissor(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgIntersectScissor:
			return (void) vg::intersectScissor(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgResetScissor:
			return vg::resetScissor(vgCtx);
			
		// nvg path
		case NCB_Constants::NCB_nvgBeginPath:
			return vg::beginPath(vgCtx);
		case NCB_Constants::NCB_nvgMoveTo:
			return vg::moveTo(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgLineTo:
			return vg::lineTo(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1]);
		case NCB_Constants::NCB_nvgBezierTo:
			return vg::cubicTo(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], c.data.argsFloats[5]);
		case NCB_Constants::NCB_nvgQuadTo:
			return vg::quadraticTo(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgArcTo:
			return vg::arcTo(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4]);
		case NCB_Constants::NCB_nvgClosePath:
			return vg::closePath(vgCtx);
			
		case NCB_Constants::NCB_nvgPathWinding:
			return ncb_error_handler::not_found("NCB_nvgPathWinding not defined for vg-renderer. Just submit everything with CW winding");
		case NCB_Constants::NCB_nvgArc:
			// direction note: vg:CW/CCW = NVG::CW/CCW - 1
			return vg::arc(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4], (c.data.argsInts[5] - 1) ? vg::Winding::CW : vg::Winding::CCW);
		case NCB_Constants::NCB_nvgRect:
			return vg::rect(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgRoundedRect:
			return vg::roundedRect(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3], c.data.argsFloats[4]);
		//case NCB_Constants::NCB_nvgRoundedRectVarying:
		//	abort(); // to many args, unused
		case NCB_Constants::NCB_nvgEllipse:
			return vg::ellipse(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2], c.data.argsFloats[3]);
		case NCB_Constants::NCB_nvgCircle:
			return vg::circle(vgCtx, c.data.argsFloats[0], c.data.argsFloats[1], c.data.argsFloats[2]);
		case NCB_Constants::NCB_nvgFill: 
			if (mDispatchSide.activePaintOrGradiantId > 0 && mDispatchSide.activePaintOrGradiantId < int(mGradients.size())) {
				vg::fillPath(vgCtx, mGradients[mDispatchSide.activePaintOrGradiantId] , vg::FillFlags::ConvexAA );
				return;
			}
			return vg::fillPath(vgCtx, mDispatchSide.activeColour.toVgColor(), vg::FillFlags::ConvexAA );
			//return vg::fill(vgCtx);
		case NCB_Constants::NCB_nvgStroke:
			if (mDispatchSide.activePaintOrGradiantId > 0 && mDispatchSide.activePaintOrGradiantId < int(mGradients.size())) {
				vg::strokePath(vgCtx, mDispatchSide.activePaintOrGradiantId );
				return;
			}
			return vg::strokePath(vgCtx, mDispatchSide.activeColour.toVgColor() , vg::FillFlags::ConvexAA );
			//return vg::stroke(vgCtx);

		// text
		case NCB_Constants::NCB_nvgFontSize:
		case NCB_Constants::NCB_nvgFontBlur:
		case NCB_Constants::NCB_nvgTextLetterSpacing:
		case NCB_Constants::NCB_nvgTextLineHeight:
		case NCB_Constants::NCB_nvgTextAlign:
		case NCB_Constants::NCB_nvgFontFaceId:
		case NCB_Constants::NCB_nvgText:
		case NCB_Constants::NCB_nvgTextBox:
			return ncb_error_handler::not_found("fontstash text functions are not defined for vg-renderer backend. You are welcome to add them yourself if you desire");
		
		// gradiants
		case NCB_Constants::NCB_nvgLinearGradient:
			{
			unsigned int idx = c.data.argsInts[0];
			if (idx < mGradientGenerators.size())
				return ncb_error_handler::error("mGradientGenerators array index out of range");
			if (vg::isValid(mGradients[idx])) {
				mDispatchSide.activePaintOrGradiantId = idx;
				return; // already defined
				}
			NCBGradientGenerator & G = mGradientGenerators[idx];
			vg::GradientHandle GH = vg::createLinearGradient(vgCtx, G.params[0], G.params[1], G.params[2], G.params[3], G.icol.toVgColor(), G.ocol.toVgColor());
			mGradients[idx] = GH;
			mDispatchSide.activePaintOrGradiantId = idx;
			}
			return;
			
		case NCB_Constants::NCB_nvgBoxGradient:
			{
			unsigned int idx = c.data.argsInts[0];
			if (idx < mGradientGenerators.size())
				return ncb_error_handler::error("mGradientGenerators array index out of range");
			if (vg::isValid(mGradients[idx])) {
				mDispatchSide.activePaintOrGradiantId = idx;
				return; // already defined
				}
			NCBGradientGenerator & G = mGradientGenerators[idx];
			vg::GradientHandle GH = vg::createBoxGradient(vgCtx, G.params[0], G.params[1], G.params[2], G.params[3], G.params[4], G.params[5], G.icol.toVgColor(), G.ocol.toVgColor());
			mGradients[idx] = GH;
			mDispatchSide.activePaintOrGradiantId = idx;
			}
			return;
			
		case NCB_Constants::NCB_nvgRadialGradient:
			{
			unsigned int idx = c.data.argsInts[0];
			if (idx < mGradientGenerators.size())
				return ncb_error_handler::error("mGradientGenerators array index out of range");
			if (vg::isValid(mGradients[idx])) {
				mDispatchSide.activePaintOrGradiantId = idx;
				return; // already defined
				}
			NCBGradientGenerator & G = mGradientGenerators[idx];
			vg::GradientHandle GH = vg::createRadialGradient(vgCtx, G.params[0], G.params[1], G.params[2], G.params[3], G.icol.toVgColor(), G.ocol.toVgColor());
			mGradients[idx] = GH;
			mDispatchSide.activePaintOrGradiantId = idx;
			}
			return;
		
			#ifdef SDL_STB_PRODUCER_CONSUMER
			case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawText:
				{
				VgRendererSSFCustomCallbackWrapper::textCallback cb;
				cb.m_producer_consumer_font_cache = m_producer_consumer_font_cache;
				cb.lastCommandId = mDispatchSide.lastCommandId;
				cb.nextCommandId = mDispatchSide.nextCommandId;
				cb.textId = c.data.argsInts[0];
				vg::customCallback(vgCtx, (void*) &cb, 0, 0);
				}
				return;
			case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerendered:
				{
				VgRendererSSFCustomCallbackWrapper::textCallback cb;
				cb.m_producer_consumer_font_cache = m_producer_consumer_font_cache;
				cb.lastCommandId = mDispatchSide.lastCommandId;
				cb.nextCommandId = mDispatchSide.nextCommandId;
				cb.textId = c.data.argsInts[0];
				cb.x = c.data.argsInts[1];
				cb.y = c.data.argsInts[2];
				vg::customCallback(vgCtx, (void*) &cb, 0, 0);
				}
				return;
			case NCB_Constants::SDL_STB_PRODUCER_CONSUMER_drawPrerenderedWColorMod:
				{
				VgRendererSSFCustomCallbackWrapper::textCallback cb;
				cb.m_producer_consumer_font_cache = m_producer_consumer_font_cache;
				cb.lastCommandId = mDispatchSide.lastCommandId;
				cb.nextCommandId = mDispatchSide.nextCommandId;
				cb.textId = c.data.argsInts[0];
				cb.x = c.data.argsInts[1];
				cb.y = c.data.argsInts[2];
				cb.r = c.data.argsInts[3];
				cb.g = c.data.argsInts[4];
				cb.b = c.data.argsInts[5];
				cb.a = c.data.argsInts[6];
				vg::customCallback(vgCtx, (void*) &cb, 0, 0);
				}
				return;
			#endif
		#endif // VGRENDERER_BACKEND
		
		
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
				customCommandHandler->handleCustomCallback(this, ctx, vgCtx, c);
			//abort(); // unknown command
			}
			return;
		}
	}


int NanoVgCommandBuffer::nvgLinearGradient(float sx, float sy, float ex, float ey, const NCBColor& icol, const NCBColor& ocol) {
	int idx = mGradientGenerators.size();
	NCBGradientGenerator ncbg;
	ncbg.type = NCB_Constants::NCB_nvgLinearGradient;
	ncbg.params[0] = sx;
	ncbg.params[1] = sy;
	ncbg.params[2] = ex;
	ncbg.params[3] = ey;
	ncbg.params[4] = 0;
	ncbg.params[5] = 0;
	ncbg.icol = icol;
	ncbg.ocol = ocol;
	mGradientGenerators.push_back(ncbg);
	return idx;
	}

int NanoVgCommandBuffer::nvgBoxGradient(float x, float y, float w, float h, float r, float f, const NCBColor& icol, const NCBColor& ocol) {
	int idx = mGradientGenerators.size();
	NCBGradientGenerator ncbg;
	ncbg.type = NCB_Constants::NCB_nvgBoxGradient;
	ncbg.params[0] = x;
	ncbg.params[1] = y;
	ncbg.params[2] = w;
	ncbg.params[3] = h;
	ncbg.params[4] = r;
	ncbg.params[5] = f;
	ncbg.icol = icol;
	ncbg.ocol = ocol;
	mGradientGenerators.push_back(ncbg);
	return idx;
	}
	
int NanoVgCommandBuffer::nvgRadialGradient(float cx, float cy, float inr, float outr, const NCBColor& icol, const NCBColor& ocol) {
	int idx = mGradientGenerators.size();
	NCBGradientGenerator ncbg;
	ncbg.type = NCB_Constants::NCB_nvgRadialGradient;
	ncbg.params[0] = cx;
	ncbg.params[1] = cy;
	ncbg.params[2] = inr;
	ncbg.params[3] = outr;
	ncbg.params[4] = 0;
	ncbg.params[5] = 0;
	ncbg.icol = icol;
	ncbg.ocol = ocol;
	mGradientGenerators.push_back(ncbg);
	return idx;
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

void NanoVgCommandBuffer::dispatch_worker (NVGcontext * ctx, vg::Context * vgCtx) {
	int sz = mCommands.size();
	
	#if NCBH_PAGEQUEUE_RANDOM_ACCESS 
		auto itt = mCommands.begin() + instructionCounter;
	#else
		auto itt = mCommands.iter_at(instructionCounter);
	#endif
	
	NanoVgCommandBuffer::dispatchState mDispatchState;
	mDispatchState.initToZero();
	
	#if NANOVG_BACKEND
	if (mPaints.size() < mGradientGenerators.size()) {
		int szOld = mPaints.size();
		int szNew = mGradientGenerators.size();
		mPaints.resize(szNew);
		memset(&mPaints[szOld], 0, sizeof(NVGpaint)*(szNew-szOld));
		}
	#endif
	#if VGRENDERER_BACKEND
	if (mGradients.size() < mGradientGenerators.size()) {
		int szOld = mGradients.size();
		int szNew = mGradientGenerators.size();
		mGradients.resize(szNew);
		for (int i = szOld; i < szNew; ++i) {
			mGradients[i].idx = UINT16_MAX;
			mGradients[i].flags = 0;
			}
		}
	#endif
	
	for (int i = instructionCounter; i < sz; ++i) {
		//GET ptr to current command, fetch next command
		auto ittThis = itt;
		++itt;
		auto ittNext = itt;
		mDispatchState.nextCommandId = NCB_Constants::NCB_unknown;
		if (i < sz -1) {
			mDispatchState.nextCommandId = (*(ittNext)).functionIdx;
			}
		dispatchSingle(ctx, vgCtx, *ittThis, mDispatchState);
		mDispatchState.lastCommandId = (*ittThis).functionIdx;
		
		// pause rendering until called again
		if (instructionCounter < 0) {
			instructionCounter = i+1;
			return;
			}
		}
	
	// reset instruction counter on completion so that the user can re-dispatch if they wish
	instructionCounter = 0;
	}
	
void NanoVgCommandBuffer::dispatch (NVGcontext * ctx) {
	dispatch_worker(ctx, NULL);
	}
	
void NanoVgCommandBuffer::dispatchVg (vg::Context * vgCtx) {
	dispatch_worker(NULL, vgCtx);
	}

void NanoVgCommandBuffer::sttr_register() {
	#ifdef STTR_CLASS_SIG
	// see snappertt/sttr on github
	#define STTR_NVG_METH(C, X, MFLAGS) regField<C,decltype(&C::X),MFLAGS>(&C::X, #X).setUserFlags(MFLAGS)
	#define STTR_NVG_PROP(C, X, MFLAGS) regField<C,decltype(&C::X),MFLAGS>(&C::X, #X).setUserFlags(MFLAGS)
	
	sttr::RegNamespace & R = *sttr::getGlobalNamespace();
	#if NANOVG_BACKEND
	R.beginClass<NVGcontext>("NVGcontext")
	.endClass();
	#endif
	R.beginClass<nvgw>("nvgw")
		.STTR_NVG_METH(nvgw, nvgRGB, 0)
		.STTR_NVG_METH(nvgw, nvgRGBf, 0)
		.STTR_NVG_METH(nvgw, nvgRGBA, 0)
		.STTR_NVG_METH(nvgw, nvgRGBAf, 0)
		.STTR_NVG_METH(nvgw, nvgLerpRGBA, 0)
		.STTR_NVG_METH(nvgw, nvgTransRGBA, 0)
		.STTR_NVG_METH(nvgw, nvgTransRGBAf, 0)
		.STTR_NVG_METH(nvgw, nvgHSL, 0)
		.STTR_NVG_METH(nvgw, nvgHSLA, 0)
		
		#if VGRENDERER_BACKEND
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_ButtMiter, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_ButtRound, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_ButtBevel, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_RoundMiter, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_RoundRound, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_RoundBevel, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_SquareMiter, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_SquareRound, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_SquareBevel, 0)
			
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_ButtMiterAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_ButtRoundAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_ButtBevelAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_RoundMiterAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_RoundRoundAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_RoundBevelAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_SquareMiterAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_SquareRoundAA, 0)
			.STTR_NVG_PROP(nvgw, VgStrokeFlag_SquareBevelAA, 0)
		#endif
	.endClass();
	//R.beginClass<NVGcolor>("NVGcolor")
	//	.STTR_NVG_PROP(NVGcolor, rgba, 0)
	//	.STTR_NVG_PROP(NVGcolor, r, 0)
	//	.STTR_NVG_PROP(NVGcolor, g, 0)
	//	.STTR_NVG_PROP(NVGcolor, b, 0)
	//	.STTR_NVG_PROP(NVGcolor, a, 0)
	//.endClass();
	//R.beginClass<NVGpaint>("NVGpaint")
	//	.STTR_NVG_PROP(NVGpaint, xform, 0)
	//	.STTR_NVG_PROP(NVGpaint, extent, 0)
	//	.STTR_NVG_PROP(NVGpaint, radius, 0)
	//	.STTR_NVG_PROP(NVGpaint, feather, 0)
	//	.STTR_NVG_PROP(NVGpaint, innerColor, 0)
	//	.STTR_NVG_PROP(NVGpaint, outerColor, 0)
	//.endClass();
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
		
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgLinearGradient, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgBoxGradient, 0)
		.STTR_NVG_METH(NanoVgCommandBuffer, nvgRadialGradient, 0)
		// text not supported
	.endClass();
	#undef STTR_NVG_METH
	#undef STTR_NVG_PROP
	#endif // STTR
	}
#endif
