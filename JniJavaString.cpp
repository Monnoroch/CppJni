#include <JniJavaString.h>


namespace JNI {

JavaString JavaString::New(JavaEnv env, const char * str) {
	return JavaString(env, str);
}

JavaString JavaString::New(JavaEnv env, const std::string& str) {
	return JavaString(env, str);
}

}
