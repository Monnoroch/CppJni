#include <JniProxy.h>
#include <JniJavaString.h>


namespace JNI {

JavaString MakeJniProxy(JavaEnv env, const char * v) {
	return JavaString(env, v);
}

JavaString MakeJniProxy(JavaEnv env, const std::string& v) {
	return JavaString(env, v);
}

const JavaString& MakeJniProxy(JavaEnv, const JavaString& v) {
	return v;
}

}
