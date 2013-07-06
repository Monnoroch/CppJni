#include <JniProxy.h>
#include <JniJavaObject.h>
#include <JniJavaString.h>
#include <JniJavaArray.h>


namespace JNI {

jobject JniToJavaProxy<JavaObject>::Val() const {
	return val.Val();
}

jstring JniToJavaProxy<JavaString>::Val() const {
	return val.Val();
}

jobject JniToJavaProxy<JavaBoolean>::Val() const {
	return val.Val();
}	

JavaObject JniFromJavaProxy<JavaObject>::Val() const {
	return JavaObject(_env, _obj);
}

JavaString JniFromJavaProxy<JavaString>::Val() const {
	return JavaString(_env, _obj);
}

JavaBoolean JniFromJavaProxy<JavaBoolean>::Val() const {
	return JavaBoolean(_env, _obj);
}

JavaArray<jboolean> JniFromJavaProxy<JavaArray<jboolean>>::Val() const {
	return JavaArray<jboolean>(_env, _obj);
}

JavaArray<jchar> JniFromJavaProxy<JavaArray<jchar>>::Val() const {
	return JavaArray<jchar>(_env, _obj);
}

JavaArray<jbyte> JniFromJavaProxy<JavaArray<jbyte>>::Val() const {
	return JavaArray<jbyte>(_env, _obj);
}

JavaArray<jshort> JniFromJavaProxy<JavaArray<jshort>>::Val() const {
	return JavaArray<jshort>(_env, _obj);
}

JavaArray<jint> JniFromJavaProxy<JavaArray<jint>>::Val() const {
	return JavaArray<jint>(_env, _obj);
}

JavaArray<jlong> JniFromJavaProxy<JavaArray<jlong>>::Val() const {
	return JavaArray<jlong>(_env, _obj);
}

JavaArray<jfloat> JniFromJavaProxy<JavaArray<jfloat>>::Val() const {
	return JavaArray<jfloat>(_env, _obj);
}

JavaArray<jdouble> JniFromJavaProxy<JavaArray<jdouble>>::Val() const {
	return JavaArray<jdouble>(_env, _obj);
}

std::string JniFromJavaProxy<std::string>::Val() const {
	return JavaString(_env, _obj).Value();
}

}
