#include <JniProxy.h>
#include <JniJavaObject.h>
#include <JniJavaException.h>
#include <JniJavaClass.h>
#include <JniJavaString.h>
#include <JniJavaArray.h>


namespace JNI {

JniToJavaProxy<JavaObject>::JniToJavaProxy(JavaEnv, const R& v) : val(v) {}

jobject JniToJavaProxy<JavaObject>::Val() const {
	return val.Val();
}

JniToJavaProxy<JavaString>::JniToJavaProxy(JavaEnv, const R& v) : val(v) {}

jstring JniToJavaProxy<JavaString>::Val() const {
	return val.Val();
}

JniToJavaProxy<JavaBoolean>::JniToJavaProxy(JavaEnv, const R& v) : val(v) {}

jobject JniToJavaProxy<JavaBoolean>::Val() const {
	return val.Val();
}

JniToJavaProxy<const char*>::JniToJavaProxy(JavaEnv env, R v) : val(env, v) {}

jstring JniToJavaProxy<const char*>::Val() const {
	return val.Val();
}

JniToJavaProxy<std::string>::JniToJavaProxy(JavaEnv env, const R& v) : val(env, v) {}

jstring JniToJavaProxy<std::string>::Val() const {
	return val.Val();
}

// JniToJavaProxy<TestIntJni>::JniToJavaProxy(JavaEnv, const R& v) : val(v) {}

// jint JniToJavaProxy<TestIntJni>::Val() const {
// 	return val.Val();
// }

//////////////////////////

JniFromJavaProxy<JavaObject>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaObject JniFromJavaProxy<JavaObject>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaException>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaException JniFromJavaProxy<JavaException>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaClass>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaClass JniFromJavaProxy<JavaClass>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaString>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaString JniFromJavaProxy<JavaString>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaBoolean>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaBoolean JniFromJavaProxy<JavaBoolean>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jboolean>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jboolean> JniFromJavaProxy<JavaArray<jboolean>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jchar>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jchar> JniFromJavaProxy<JavaArray<jchar>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jbyte>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jbyte> JniFromJavaProxy<JavaArray<jbyte>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jshort>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jshort> JniFromJavaProxy<JavaArray<jshort>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jint>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jint> JniFromJavaProxy<JavaArray<jint>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jlong>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jlong> JniFromJavaProxy<JavaArray<jlong>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jfloat>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jfloat> JniFromJavaProxy<JavaArray<jfloat>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<JavaArray<jdouble>>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

JavaArray<jdouble> JniFromJavaProxy<JavaArray<jdouble>>::Val() const {
	return R(_env, _obj);
}

JniFromJavaProxy<std::string>::JniFromJavaProxy(JavaEnv env, jobject obj) : _env(env), _obj((jtype) obj) {}

std::string JniFromJavaProxy<std::string>::Val() const {
	return JavaString(_env, _obj).Value();
}

}
