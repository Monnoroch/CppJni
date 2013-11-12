#pragma once
#ifndef JNI_JAVA_EXCEPTION_H
#define JNI_JAVA_EXCEPTION_H

#include <JniForwards.h>
#include <JniJavaObject.h>


namespace JNI {

class JavaException : public JavaObject {
public:
	JavaException();
	JavaException(JavaEnv env, jthrowable c);
	JavaException(const JavaException& c);
	JavaException(JavaException&& c);

	virtual ~JavaException();

	JavaException& operator=(const JavaException& cls);
	JavaException& operator=(JavaException&& cls);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaException& cls) const;
	bool operator!=(const JavaException& cls) const;

	jthrowable Val() const;
	jint Throw() const;
};

}

#endif
