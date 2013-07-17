#include <JniSignatureBuilder.h>


namespace JNI {

std::string JniSignatureBuilder<void>::Signature() {
	return "V";
}

std::string JniSignatureBuilder<jboolean>::Signature() {
	return "Z";
}

std::string JniSignatureBuilder<jchar>::Signature() {
	return "C";
}

std::string JniSignatureBuilder<jbyte>::Signature() {
	return "B";
}

std::string JniSignatureBuilder<jshort>::Signature() {
	return "S";
}

std::string JniSignatureBuilder<jint>::Signature() {
	return "I";
}

std::string JniSignatureBuilder<jlong>::Signature() {
	return "J";
}

std::string JniSignatureBuilder<jfloat>::Signature() {
	return "F";
}

std::string JniSignatureBuilder<jdouble>::Signature() {
	return "D";
}

std::string JniSignatureBuilder<JavaObject>::Signature() {
	return "Ljava/lang/Object;";
}

std::string JniSignatureBuilder<JavaClass>::Signature() {
	return "Ljava/lang/Class;";
}

std::string JniSignatureBuilder<JavaString>::Signature() {
	return "Ljava/lang/String;";
}

std::string JniSignatureBuilder<JavaBoolean>::Signature() {
	return "Ljava/lang/Boolean;";
}

std::string JniSignatureBuilder<std::string>::Signature() {
	return JniSignatureBuilder<JavaString>::Signature();
}

// std::string JniSignatureBuilder<TestJniInt>::Signature() {
// 	return "I";
// }

} // JNI
