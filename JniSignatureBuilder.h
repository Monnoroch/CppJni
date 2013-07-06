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
	static std::string Signature() {
		return "V";
	}
};

template<>
struct JniSignatureBuilder<jboolean> {
	static std::string Signature() {
		return "Z";
	}
};

template<>
struct JniSignatureBuilder<jchar> {
	static std::string Signature() {
		return "C";
	}
};

template<>
struct JniSignatureBuilder<jbyte> {
	static std::string Signature() {
		return "B";
	}
};

template<>
struct JniSignatureBuilder<jshort> {
	static std::string Signature() {
		return "S";
	}
};

template<>
struct JniSignatureBuilder<jint> {
	static std::string Signature() {
		return "I";
	}
};

template<>
struct JniSignatureBuilder<jlong> {
	static std::string Signature() {
		return "J";
	}
};

template<>
struct JniSignatureBuilder<jfloat> {
	static std::string Signature() {
		return "F";
	}
};

template<>
struct JniSignatureBuilder<jdouble> {
	static std::string Signature() {
		return "D";
	}
};

template<>
struct JniSignatureBuilder<JavaObject> {
	static std::string Signature() {
		return "Ljava/lang/Object;";
	}
};

template<>
struct JniSignatureBuilder<JavaClass> {
	static std::string Signature() {
		return "Ljava/lang/Class;";
	}
};

template<>
struct JniSignatureBuilder<JavaString> {
	static std::string Signature() {
		return "Ljava/lang/String;";
	}
};

template<>
struct JniSignatureBuilder<JavaBoolean> {
	static std::string Signature() {
		return "Ljava/lang/Boolean;";
	}
};

template<typename T>
struct JniSignatureBuilder<JavaArray<T>> {
	static std::string Signature() {
		return "[" + JniSignatureBuilder<T>::Signature();
	}
};

template<>
struct JniSignatureBuilder<std::string> {
	static std::string Signature() {
		return JniSignatureBuilder<JavaString>::Signature();
	}
};

template<typename T>
struct JniSignatureBuilder<std::vector<T>> {
	static std::string Signature() {
		return JniSignatureBuilder<JavaArray<T>>::Signature();
	}
};

template<>
struct JniSignatureBuilder<TestJniInt> {
	static std::string Signature() {
		return "I";
	}
};


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
