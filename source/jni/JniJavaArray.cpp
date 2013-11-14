#include <JniJavaArray.h>


namespace JNI {

JavaArray<jboolean>::JavaArray() : JavaObject() {}
JavaArray<jboolean>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewBooleanArray(size)) {}
JavaArray<jboolean>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jboolean>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jboolean>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jboolean>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jboolean> JavaArray<jboolean>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jboolean> JavaArray<jboolean>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jboolean>::~JavaArray() {}

JavaArray<jboolean>& JavaArray<jboolean>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jboolean>& JavaArray<jboolean>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jboolean>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jboolean>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jboolean>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jboolean>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jboolean JavaArray<jboolean>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jboolean>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jboolean JavaArray<jboolean>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jboolean>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jbooleanArray JavaArray<jboolean>::Val() const {
	return (Arr) _obj;
}

std::vector<jboolean> JavaArray<jboolean>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jboolean>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetBooleanArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jboolean>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetBooleanArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jchar>::JavaArray() : JavaObject() {}
JavaArray<jchar>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewCharArray(size)) {}
JavaArray<jchar>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jchar>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jchar>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jchar>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jchar> JavaArray<jchar>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jchar> JavaArray<jchar>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jchar>::~JavaArray() {}

JavaArray<jchar>& JavaArray<jchar>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jchar>& JavaArray<jchar>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jchar>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jchar>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jchar>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jchar>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jchar JavaArray<jchar>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jchar>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jchar JavaArray<jchar>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jchar>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jcharArray JavaArray<jchar>::Val() const {
	return (Arr) _obj;
}

std::vector<jchar> JavaArray<jchar>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jchar>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetCharArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jchar>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetCharArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jbyte>::JavaArray() : JavaObject() {}
JavaArray<jbyte>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewByteArray(size)) {}
JavaArray<jbyte>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jbyte>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jbyte>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jbyte>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jbyte> JavaArray<jbyte>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jbyte> JavaArray<jbyte>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jbyte>::~JavaArray() {}

JavaArray<jbyte>& JavaArray<jbyte>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jbyte>& JavaArray<jbyte>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jbyte>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jbyte>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jbyte>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jbyte>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jbyte JavaArray<jbyte>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jbyte>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jbyte JavaArray<jbyte>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jbyte>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jbyteArray JavaArray<jbyte>::Val() const {
	return (Arr) _obj;
}

std::vector<jbyte> JavaArray<jbyte>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jbyte>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetByteArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jbyte>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetByteArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jshort>::JavaArray() : JavaObject() {}
JavaArray<jshort>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewShortArray(size)) {}
JavaArray<jshort>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jshort>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jshort>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jshort>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jshort> JavaArray<jshort>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jshort> JavaArray<jshort>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jshort>::~JavaArray() {}

JavaArray<jshort>& JavaArray<jshort>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jshort>& JavaArray<jshort>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jshort>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jshort>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jshort>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jshort>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jshort JavaArray<jshort>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jshort>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jshort JavaArray<jshort>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jshort>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jshortArray JavaArray<jshort>::Val() const {
	return (Arr) _obj;
}

std::vector<jshort> JavaArray<jshort>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jshort>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetShortArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jshort>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetShortArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jint>::JavaArray() : JavaObject() {}
JavaArray<jint>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
JavaArray<jint>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jint>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jint>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jint>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jint> JavaArray<jint>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jint> JavaArray<jint>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jint>::~JavaArray() {}

JavaArray<jint>& JavaArray<jint>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jint>& JavaArray<jint>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jint>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jint>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jint>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jint>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jint JavaArray<jint>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jint>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jint JavaArray<jint>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jint>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jintArray JavaArray<jint>::Val() const {
	return (Arr) _obj;
}

std::vector<jint> JavaArray<jint>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jint>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetIntArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jint>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetIntArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jlong>::JavaArray() : JavaObject() {}
JavaArray<jlong>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewLongArray(size)) {}
JavaArray<jlong>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jlong>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jlong>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jlong>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jlong> JavaArray<jlong>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jlong> JavaArray<jlong>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jlong>::~JavaArray() {}

JavaArray<jlong>& JavaArray<jlong>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jlong>& JavaArray<jlong>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jlong>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jlong>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jlong>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jlong>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jlong JavaArray<jlong>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jlong>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jlong JavaArray<jlong>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jlong>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jlongArray JavaArray<jlong>::Val() const {
	return (Arr) _obj;
}

std::vector<jlong> JavaArray<jlong>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jlong>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetLongArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jlong>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetLongArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jfloat>::JavaArray() : JavaObject() {}
JavaArray<jfloat>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewFloatArray(size)) {}
JavaArray<jfloat>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jfloat>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jfloat>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jfloat>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jfloat> JavaArray<jfloat>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jfloat> JavaArray<jfloat>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jfloat>::~JavaArray() {}

JavaArray<jfloat>& JavaArray<jfloat>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jfloat>& JavaArray<jfloat>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jfloat>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jfloat>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jfloat>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jfloat>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jfloat JavaArray<jfloat>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jfloat>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jfloat JavaArray<jfloat>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jfloat>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jfloatArray JavaArray<jfloat>::Val() const {
	return (Arr) _obj;
}

std::vector<jfloat> JavaArray<jfloat>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jfloat>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetFloatArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jfloat>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetFloatArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<jdouble>::JavaArray() : JavaObject() {}
JavaArray<jdouble>::JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewDoubleArray(size)) {}
JavaArray<jdouble>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
	SetData(0, val.size(), &val[0]);
}
JavaArray<jdouble>::JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
JavaArray<jdouble>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<jdouble>::JavaArray(JavaArray&& a) : JavaObject(a) {}

JavaArray<jdouble> JavaArray<jdouble>::New(JavaEnv env, jsize len) {
	return JavaArray(env, len);
};

JavaArray<jdouble> JavaArray<jdouble>::New(JavaEnv env, const std::vector<Elem>& arr) {
	return JavaArray(env, arr);
}

JavaArray<jdouble>::~JavaArray() {}

JavaArray<jdouble>& JavaArray<jdouble>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<jdouble>& JavaArray<jdouble>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<jdouble>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<jdouble>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<jdouble>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<jdouble>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

jdouble JavaArray<jdouble>::Get(jsize n) const {
	Elem res;
	GetData(n, 1, &res);
	return res;
}

void JavaArray<jdouble>::Set(jsize n, Elem val) {
	SetData(n, 1, &val);
}

// TODO: operator[]

jdouble JavaArray<jdouble>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<jdouble>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jdoubleArray JavaArray<jdouble>::Val() const {
	return (Arr) _obj;
}

std::vector<jdouble> JavaArray<jdouble>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	GetData(0, len, &res[0]);
	return res;
}

void JavaArray<jdouble>::GetData(jsize from, jsize len, Elem * ptr) const {
	_env.Val()->GetDoubleArrayRegion(Val(), from, len, ptr);
}

void JavaArray<jdouble>::SetData(jsize from, jsize len, const Elem * ptr) {
	_env.Val()->SetDoubleArrayRegion(Val(), from, len, ptr);
}

///////////////////////////////////////

JavaArray<JavaObject>::JavaArray() : JavaObject() {}
// JavaArray<JavaObject>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
// 	FromVector(val);
// }
JavaArray<JavaObject>::JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
JavaArray<JavaObject>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<JavaObject>::JavaArray(JavaArray&& a) : JavaObject(a) {}
JavaArray<JavaObject>::~JavaArray() {}

JavaArray<JavaObject>& JavaArray<JavaObject>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<JavaObject>& JavaArray<JavaObject>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<JavaObject>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<JavaObject>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<JavaObject>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<JavaObject>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

JavaObject JavaArray<JavaObject>::Get(jsize n) const {
	return FromJavaProxy<Elem>(_env, _env.Val()->GetObjectArrayElement(Val(), n)).Val();
}

void JavaArray<JavaObject>::Set(jsize n, const Elem& val) {
	_env.Val()->SetObjectArrayElement(Val(), n, ToJavaProxy<Elem>(_env, val).Val());
}

// TODO: operator[]

JavaObject JavaArray<JavaObject>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<JavaObject>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jobjectArray JavaArray<JavaObject>::Val() const {
	return (Arr) _obj;
}

std::vector<JavaObject> JavaArray<JavaObject>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	for(jsize i = 0; i < len; ++i)
		res[i] = Get(i);
	return res;
}

void JavaArray<JavaObject>::FromVector(const std::vector<Elem>& vec) {
	jsize len = vec.size();
	for(jsize i = 0; i < len; ++i)
		Set(i, vec[i]);
}

///////////////////////////////////////

JavaArray<JavaString>::JavaArray() : JavaObject() {}
// JavaArray<JavaString>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
// 	FromVector(val);
// }
JavaArray<JavaString>::JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
JavaArray<JavaString>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<JavaString>::JavaArray(JavaArray&& a) : JavaObject(a) {}
JavaArray<JavaString>::~JavaArray() {}

JavaArray<JavaString>& JavaArray<JavaString>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<JavaString>& JavaArray<JavaString>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<JavaString>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<JavaString>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<JavaString>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<JavaString>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

JavaString JavaArray<JavaString>::Get(jsize n) const {
	return FromJavaProxy<Elem>(_env, _env.Val()->GetObjectArrayElement(Val(), n)).Val();
}

void JavaArray<JavaString>::Set(jsize n, const Elem& val) {
	_env.Val()->SetObjectArrayElement(Val(), n, ToJavaProxy<Elem>(_env, val).Val());
}

// TODO: operator[]

JavaString JavaArray<JavaString>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<JavaString>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jobjectArray JavaArray<JavaString>::Val() const {
	return (Arr) _obj;
}

std::vector<JavaString> JavaArray<JavaString>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	for(jsize i = 0; i < len; ++i)
		res[i] = Get(i);
	return res;
}

void JavaArray<JavaString>::FromVector(const std::vector<Elem>& vec) {
	jsize len = vec.size();
	for(jsize i = 0; i < len; ++i)
		Set(i, vec[i]);
}

///////////////////////////////////////

JavaArray<std::string>::JavaArray() : JavaObject() {}
// JavaArray<std::string>::JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
// 	FromVector(val);
// }
JavaArray<std::string>::JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
JavaArray<std::string>::JavaArray(const JavaArray& a) : JavaObject(a) {}
JavaArray<std::string>::JavaArray(JavaArray&& a) : JavaObject(a) {}
JavaArray<std::string>::~JavaArray() {}

JavaArray<std::string>& JavaArray<std::string>::operator=(const JavaArray& arr) {
	JavaObject::operator=(arr);
	return *this;
}

JavaArray<std::string>& JavaArray<std::string>::operator=(JavaArray&& arr) {
	JavaObject::operator=(std::move(arr));
	return *this;
}

bool JavaArray<std::string>::operator==(const JavaArray& arr) const {
	if(JavaObject::operator==(arr))
		return true;

	jsize l1 = Length(), l2 = arr.Length();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr.ToVector();
}

bool JavaArray<std::string>::operator!=(const JavaArray& arr) const {
	return !(*this == arr);
}

bool JavaArray<std::string>::operator==(const std::vector<Elem>& arr) const {
	jsize l1 = Length(), l2 = arr.size();
	if(l1 != l2)
		return false;
	
	return ToVector() == arr;
}

bool JavaArray<std::string>::operator!=(const std::vector<Elem>& arr) const {
	return !(*this == arr);
}

std::string JavaArray<std::string>::Get(jsize n) const {
	return FromJavaProxy<Elem>(_env, _env.Val()->GetObjectArrayElement(Val(), n)).Val();
}

void JavaArray<std::string>::Set(jsize n, const Elem& val) {
	_env.Val()->SetObjectArrayElement(Val(), n, ToJavaProxy<Elem>(_env, val).Val());
}

// TODO: operator[]

std::string JavaArray<std::string>::operator[](jsize n) const {
	return Get(n);
}

jsize JavaArray<std::string>::Length() const {
	return _env.Val()->GetArrayLength(Val());
}

jobjectArray JavaArray<std::string>::Val() const {
	return (Arr) _obj;
}

std::vector<std::string> JavaArray<std::string>::ToVector() const {
	jsize len = Length();
	std::vector<Elem> res(len);
	for(jsize i = 0; i < len; ++i)
		res[i] = Get(i);
	return res;
}

void JavaArray<std::string>::FromVector(const std::vector<Elem>& vec) {
	jsize len = vec.size();
	for(jsize i = 0; i < len; ++i)
		Set(i, vec[i]);
}

}
