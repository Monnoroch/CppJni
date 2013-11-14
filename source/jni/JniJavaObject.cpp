#include <JniJavaObjectClassDef.h>
#include <JniJavaClass.h>


namespace JNI {

#ifdef MSYM_DEBUG_JNI_REF_CNT
int globalRefCnt = 0;
#endif

JavaObject::JavaObject() : JavaObject(JavaEnv(), nullptr) {}
JavaObject::JavaObject(JavaEnv env, jobject o) : _env(env), _obj(o) {
#ifdef MSYM_DEBUG_JNI_REF_CNT
	if(Valid())
		globalRefCnt++;
#endif
}

JavaObject::JavaObject(const JavaObjectIniter& o) : JavaObject(o.env, o.obj) {}
JavaObject::JavaObject(const JavaObject& o) {
	Init(o);
}
JavaObject::JavaObject(JavaObject&& o) : _env(o._env), _obj(o._obj) {
	o._env = JavaEnv();
	o._obj = nullptr;
}

JavaObject& JavaObject::operator=(const JavaObject& o) {
	Reset(o);
	return *this;
}

JavaObject& JavaObject::operator=(JavaObject&& o) {
	std::swap(_env, o._env);
	std::swap(_obj, o._obj);
	return *this;
}

JavaObject::~JavaObject() {
	Destroy();
}

bool JavaObject::operator==(const JavaObject& obj) const {
	return _env.Val()->IsSameObject(Val(), obj.Val());
}

bool JavaObject::operator!=(const JavaObject& obj) const {
	return !(*this == obj);
}

JavaClass JavaObject::GetClass() const {
	return JavaClass(_env, _env.Val()->GetObjectClass(Val()));
}

JavaObject JavaObject::New(const JavaClass& cls) {
	return cls.NewObject(); // JavaObject(cls._env, cls._env.Val()->AllocObject(cls.Val()));
}

JavaObject JavaObject::New(JavaEnv env, const std::string& cls) {
	return New(env.FindClass(cls));
}

bool JavaObject::Valid() const {
	return _env.Valid() && _obj != nullptr;
}

JavaEnv JavaObject::Env() const {
	return _env;
}

jobject JavaObject::Val() const {
	return _obj;
}

jint JavaObject::MonitorEnter() const {
	return _env.Val()->MonitorEnter(Val());
}

jint JavaObject::MonitorExit() const {
	return _env.Val()->MonitorExit(Val());
}

void JavaObject::Reset(const JavaObject& o) {
	Destroy();
	Init(o);
}

void JavaObject::Init(const JavaObject& o) {
	_env = o._env;
	if(o.Valid()) {
#ifdef MSYM_DEBUG_JNI_REF_CNT
	globalRefCnt++;
#endif
		_obj = _env.Val()->NewLocalRef(o._obj);
	}
}

void JavaObject::Destroy() {
	if(Valid()) {
#ifdef MSYM_DEBUG_JNI_REF_CNT
	globalRefCnt--;
#endif
		_env.Val()->DeleteLocalRef(_obj);
	}
}

}
