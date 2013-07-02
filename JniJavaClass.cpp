#include <JniJavaClass.h>
#include <JniJavaEnv.h>
#include <JniJavaMethod.h>


namespace JNI {

jclass JavaClass::GetClass(JavaEnv env, const char * name) {
	if(!env.Valid()) {
		printf("Cannot load class %s, broken JavaEnv.", name);
		return 0;
	}

	jclass cls = 0;
	bool dot = false;
	const char * tmp = name;
	while(*tmp != '\0') {
		if(*tmp == '.') {
			dot = true;
			break;
		}
		tmp++;
	}
	if(dot) {
		std::string s(name);
		for(size_t index = 0; index = s.find(".", index), index != std::string::npos;) {
			s.replace(index, 1, "/");
			index++;
		}
		cls = env.Val()->FindClass(s.c_str());
	}
	else cls = env.Val()->FindClass(name);

	if(cls == 0)
		printf("Cannot find class %s.", name);

	return cls;
}

JavaClass JavaClass::New(JavaEnv env, const char * str) {
	return JavaClass(env, str);
}

JavaClass JavaClass::New(JavaEnv env, const std::string& str) {
	return JavaClass(env, str);
}

JavaObject JavaClass::NewObject() const {
	return JavaObject(_env, _env.Val()->NewObject(Val(), GetDefaultConstructor().Val()));
}

JavaStaticMethod<void()> JavaClass::GetDefaultConstructor() const {
	return GetConstructor<void()>();
}

}
