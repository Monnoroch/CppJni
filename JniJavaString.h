#pragma once
#ifndef JNI_JAVA_STRING_H
#define JNI_JAVA_STRING_H

#include <JniForwards.h>
#include <JniJavaObjectClassDef.h>


namespace JNI {

class JavaString : public JavaObject {
public:
	JavaString();
	JavaString(JavaEnv env, const char * val);
	JavaString(JavaEnv env, const std::string& val);
	JavaString(JavaEnv env, jstring str);
	JavaString(const JavaString& str);
	JavaString(JavaString&& str);

	static JavaString New(JavaEnv env, const char * str);
	static JavaString New(JavaEnv env, const std::string& str);

	virtual ~JavaString();

	JavaString& operator=(const JavaString& str);
	JavaString& operator=(JavaString&& str);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaString& str) const;
	bool operator!=(const JavaString& obj) const;
	bool operator==(const std::string& str) const;
	bool operator!=(const std::string& str) const;

	friend bool operator==(const std::string& str, const JavaString& self) {
		return self == str;
	}

	friend bool operator!=(const std::string& str, const JavaString& self) {
		return self != str;
	}

	char operator[](size_t n) const;

	jstring Val() const;
	const char * Value() const;
	jsize Length() const;
	jsize Size() const;

private:
	const char * val;

	void Init();
	void Destroy();

protected:
	void Reset(const JavaString& str);
};

}

#endif
