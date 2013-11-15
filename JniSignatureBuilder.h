#pragma once
#ifndef JNI_SIGNATURE_BUILDER_H
#define JNI_SIGNATURE_BUILDER_H

#include <JniForwards.h>


namespace JNI {

template<typename R, typename ... Args>
struct JniSignatureBuilder {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<void> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jboolean> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jchar> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jbyte> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jshort> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jint> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jlong> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jfloat> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<jdouble> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<JavaObject> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<JavaClass> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<JavaString> {
	static std::string Signature();
};

template<>
struct JniSignatureBuilder<JavaBoolean> {
	static std::string Signature();
};

template<typename T>
struct JniSignatureBuilder<JavaArray<T>> {
	static std::string Signature() {
		return "[" + JniSignatureBuilder<T>::Signature();
	}
};

template<>
struct JniSignatureBuilder<std::string> {
	static std::string Signature();
};

template<typename T>
struct JniSignatureBuilder<std::vector<T>> {
	static std::string Signature() {
		return JniSignatureBuilder<JavaArray<T>>::Signature();
	}
};

// template<>
// struct JniSignatureBuilder<TestJniInt> {
// 	static std::string Signature();
// };


template<typename R, typename ... Args>
struct JniSignatureBuilder<R(Args...)> {
	// Template-magic string concatenation
	static std::string Acc() {
		return "";
	}
	template<typename ... As>
	static std::string Acc(const std::string& a, As&& ... as) {
		return a + Acc(std::forward<As>(as)...);
	}

	static std::string Signature() {
		return "(" + Acc(JniSignatureBuilder<Args>::Signature()...) + ")" + JniSignatureBuilder<R>::Signature();
	}
};

}

#endif
