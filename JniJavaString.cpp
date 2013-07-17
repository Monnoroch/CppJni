#include <JniJavaString.h>


namespace JNI {

JavaString::JavaString() : JavaObject() {}
JavaString::JavaString(JavaEnv env, const char * val) : JavaString(env, env.Val()->NewStringUTF(val)) {}
JavaString::JavaString(JavaEnv env, const std::string& val) : JavaString(env, val.c_str()) {}
JavaString::JavaString(JavaEnv env, jstring str) : JavaObject(env, str) {
	Init();
}
JavaString::JavaString(const JavaString& str) : JavaObject(str) {
	Init();
}
JavaString::JavaString(JavaString&& str) : JavaObject(str), val(str.val) {
	str.val = nullptr;
}

JavaString::~JavaString() {
	JavaString::Destroy();
}

JavaString& JavaString::operator=(const JavaString& str) {
	JavaString::Reset(str);
	return *this;
}

JavaString& JavaString::operator=(JavaString&& str) {
	(void) JavaObject::operator=(std::move(str));
	std::swap(val, str.val);
	return *this;
}

bool JavaString::operator==(const JavaString& str) const {
	if(JavaObject::operator==(str))
		return true;

	jsize l1 = Length(), l2 = str.Length();
	if(l1 != l2)
		return false;
	return std::string(Value()) == str.Value();
}

bool JavaString::operator!=(const JavaString& obj) const {
	return !(*this == obj);
}

bool JavaString::operator==(const std::string& str) const {
	jsize len = Length();
	if(len != (jsize) str.length())
		return false;
	return str == Value();
}

bool JavaString::operator!=(const std::string& str) const {
	return !(*this == str);
}

char JavaString::operator[](size_t n) const {
	return val[n];
}

jstring JavaString::Val() const {
	return (jstring) _obj;
}

const char * JavaString::Value() const {
	return val;
}

jsize JavaString::Length() const {
	return _env.Val()->GetStringLength(Val());
}

jsize JavaString::Size() const {
	return _env.Val()->GetStringUTFLength(Val());
}

void JavaString::Init() {
	if(Valid())
		val = _env.Val()->GetStringUTFChars(Val(), nullptr);
}

void JavaString::Destroy() {
	if(Valid())
		_env.Val()->ReleaseStringUTFChars(Val(), val);
}

void JavaString::Reset(const JavaString& str) {
	Destroy();
	JavaObject::Reset(str);
	Init();
}

JavaString JavaString::New(JavaEnv env, const char * str) {
	return JavaString(env, str);
}

JavaString JavaString::New(JavaEnv env, const std::string& str) {
	return JavaString(env, str);
}

}
