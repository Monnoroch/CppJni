#pragma once
#ifndef JNI_JAVA_STRING_H
#define JNI_JAVA_STRING_H

#include <JniForwards.h>
#include <JniJavaObject.h>


namespace JNI {

class JavaString : public JavaObject {
private:
	void Init() {
		if(Valid())
			val = _env.Val()->GetStringUTFChars(Val(), nullptr);
	}

	void Destroy() {
		if(Valid())
			_env.Val()->ReleaseStringUTFChars(Val(), val);
	}

protected:
	void Reset(const JavaString& str) {
		Destroy();
		JavaObject::Reset(str);
		Init();
	}

public:
	JavaString() : JavaObject() {}
	JavaString(JavaEnv env, const char * val) : JavaObject(env, env.Val()->NewStringUTF(val)) {
		Init();
	}
	JavaString(JavaEnv env, const std::string& val) : JavaString(env, val.c_str()) {}
	JavaString(JavaEnv env, jstring str) : JavaObject(env, str) {
		Init();
	}
	JavaString(const JavaString& str) : JavaObject(str) {
		Init();
	}
	JavaString(JavaString&& str) : JavaObject(str), val(str.val) {
		str.val = nullptr;
	}

	static JavaString New(JavaEnv env, const char * str);
	static JavaString New(JavaEnv env, const std::string& str);

	virtual ~JavaString() {
		JavaString::Destroy();
	}

	JavaString& operator=(const JavaString& str) {
		JavaString::Reset(str);
		return *this;
	}

	JavaString& operator=(JavaString&& str) {
		(void) JavaObject::operator=(std::move(str));
		std::swap(val, str.val);
		return *this;
	}

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaString& str) const {
		if(JavaObject::operator==(str))
			return true;

		jsize l1 = Length(), l2 = str.Length();
		if(l1 != l2)
			return false;
		return std::string(Value()) == str.Value();
	}

	bool operator!=(const JavaString& obj) const {
		return !(*this == obj);
	}

	bool operator==(const std::string& str) const {
		jsize len = Length();
		if(len != (jsize) str.length())
			return false;
		return str == Value();
	}

	bool operator!=(const std::string& str) const {
		return !(*this == str);
	}

	friend bool operator==(const std::string& str, const JavaString& self) {
		return self == str;
	}

	friend bool operator!=(const std::string& str, const JavaString& self) {
		return self != str;
	}

	char operator[](size_t n) const {
		return val[n];
	}

	jstring Val() const { return (jstring) _obj; }

	const char * Value() const {
		return val;
	}

	jsize Length() const {
		return _env.Val()->GetStringLength(Val());
	}

	jsize Size() const {
		return _env.Val()->GetStringUTFLength(Val());
	}

private:
	const char * val;
};

}

#endif
