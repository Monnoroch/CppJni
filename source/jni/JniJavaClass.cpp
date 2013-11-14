#include <JniJavaClass.h>
#include <JniJavaEnv.h>
#include <JniJavaMethod.h>


namespace JNI {

JavaClass::JavaClass() : JavaObject() {}
JavaClass::JavaClass(JavaEnv env, jclass c) : JavaObject(env, c) {}
JavaClass::JavaClass(JavaEnv env, const char * val) : JavaClass(env, GetClass(env, val)) {}
JavaClass::JavaClass(JavaEnv env, const std::string& val) : JavaClass(env, GetClass(env, val.c_str())) {}
JavaClass::JavaClass(const JavaClass& c) : JavaObject(c) {}
JavaClass::JavaClass(JavaClass&& c) : JavaObject(c) {}

JavaClass::~JavaClass() {}

JavaClass& JavaClass::operator=(const JavaClass& cls) {
	JavaObject::operator=(cls);
	return *this;
}

JavaClass& JavaClass::operator=(JavaClass&& cls) {
	JavaObject::operator=(std::move(cls));
	return *this;
}

bool JavaClass::operator==(const JavaClass& cls) const {
	return JavaObject::operator==(cls);
}

bool JavaClass::operator!=(const JavaClass& cls) const {
	return JavaObject::operator!=(cls);
}

bool JavaClass::operator==(const std::string& str) const {
	return *this == _env.FindClass(str);
}

bool JavaClass::operator!=(const std::string& str) const {
	return !(*this == str);
}

jclass JavaClass::GetClass(JavaEnv env, const char * name) {
	if(!env.Valid()) {
		printf("Cannot load class %s, broken JavaEnv.", name);
		return nullptr;
	}

	jclass cls = nullptr;
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

	if(cls == nullptr)
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
	return NewObject<void>();
}

JavaStaticMethod<void()> JavaClass::GetDefaultConstructor() const {
	return GetConstructor<void()>();
}

jclass JavaClass::Val() const {
	return (jclass) _obj;
}

JavaClass JavaClass::Superclass() const {
	return JavaClass(_env, _env.Val()->GetSuperclass(Val()));
}

jboolean JavaClass::IsAssignableFrom(const JavaClass& cls) const {
	return _env.Val()->IsAssignableFrom(Val(), cls.Val());
}

}
