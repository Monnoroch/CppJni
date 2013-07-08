#pragma once
#ifndef JNI_JAVA_EXCEPTION_H
#define JNI_JAVA_EXCEPTION_H

#include <JniForwards.h>
#include <JniProxy.h>
#include <JniJavaObject.h>
#include <JniSignatureBuilder.h>


namespace JNI {

class JavaException : public JavaObject {
public:
	JavaException() : JavaObject() {}
	JavaException(JavaEnv env, jthrowable c) : JavaObject(env, c) {}
	JavaException(const JavaException& c) : JavaObject(c) {}
	JavaException(JavaException&& c) : JavaObject(c) {}

	virtual ~JavaException() {}

	JavaException& operator=(const JavaException& cls) {
		JavaObject::operator=(cls);
		return *this;
	}

	JavaException& operator=(JavaException&& cls) {
		JavaObject::operator=(std::move(cls));
		return *this;
	}

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaException& cls) const {
		return JavaObject::operator==(cls);
	}

	bool operator!=(const JavaException& cls) const {
		return JavaObject::operator!=(cls);
	}

	jthrowable Val() const { return (jthrowable) _obj; }

	jint Throw() const {
		return Env().Val()->Throw(Val());
	}
};

}

#endif
