#include <JniJavaException.h>


namespace JNI {

JavaException::JavaException() : JavaObject() {}
JavaException::JavaException(JavaEnv env, jthrowable c) : JavaObject(env, c) {}
JavaException::JavaException(const JavaException& c) : JavaObject(c) {}
JavaException::JavaException(JavaException&& c) : JavaObject(c) {}

JavaException::~JavaException() {}

JavaException& JavaException::operator=(const JavaException& cls) {
	JavaObject::operator=(cls);
	return *this;
}

JavaException& JavaException::operator=(JavaException&& cls) {
	JavaObject::operator=(std::move(cls));
	return *this;
}

bool JavaException::operator==(const JavaException& cls) const {
	return JavaObject::operator==(cls);
}

bool JavaException::operator!=(const JavaException& cls) const {
	return JavaObject::operator!=(cls);
}

jthrowable JavaException::Val() const {
	return (jthrowable) _obj;
}

jint JavaException::Throw() const {
	return Env().Val()->Throw(Val());
}

}
