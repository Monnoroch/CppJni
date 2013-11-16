#pragma once
#ifndef JNI_JAVA_OBJECT_OTHER_DEFS_H
#define JNI_JAVA_OBJECT_OTHER_DEFS_H

#include <JniForwards.h>
#include <JniJavaEnv.h>
#include <JniJavaObjectClassDef.h>
#include <JniJavaClassClassDef.h>

namespace JNI {

template<typename T>
JavaMethod<T> JavaObject::GetMethod(const char * name) const {
	return GetClass().GetMethod<T>(*this, name);
}

template<typename T>
JavaField<T> JavaObject::GetField(const char * name) const {
	return GetClass().GetField<T>(*this, name);
}

template<typename R, typename ... Args>
JavaObject JavaObject::New(const JavaClass& cls, Args&& ... args) {
	return cls.NewObject<R, Args...>(std::forward<Args>(args)...);
}

template<typename R, typename ... Args>
JavaObject JavaObject::New(JavaEnv env, const std::string& cls, Args&& ... args) {
	return New(env.FindClass(cls), std::forward<Args>(args)...);
}

}

#endif
