#pragma once
#ifndef JNI_JAVA_CLASS_OTHER_DEFS_H
#define JNI_JAVA_CLASS_OTHER_DEFS_H

#include <JniForwards.h>
#include <JniSignatureBuilder.h>
#include <JniJavaClassClassDef.h>

namespace JNI {

template<typename R, typename ... Args>
struct JavaClass::MethodGetter<R(Args...)> {
	jmethodID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetMethodID(self.Val(), name, JniSignatureBuilder<R(Args...)>::Signature().c_str());
	}
};

template<typename R, typename ... Args>
struct JavaClass::StaticMethodGetter<R(Args...)> {
	jmethodID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetStaticMethodID(self.Val(), name, JniSignatureBuilder<R(Args...)>::Signature().c_str());
	}
};

template<typename T>
struct JavaClass::FieldGetter {
	jfieldID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetFieldID(self.Val(), name, JniSignatureBuilder<T>::Signature().c_str());
	}
};

template<typename T>
struct JavaClass::StaticFieldGetter {
	jfieldID Get(const JavaClass& self, const char * name) const {
		return self.Env().Val()->GetStaticFieldID(self.Val(), name, JniSignatureBuilder<T>::Signature().c_str());
	}
};

}

#endif
