#pragma once
#ifndef JNI_JAVA_ARRAY_H
#define JNI_JAVA_ARRAY_H

#include <JniForwards.h>
#include <JniJavaObject.h>


namespace JNI {

template<>
class JavaArray<jboolean> : public JavaObject {
	typedef jboolean Elem;
	typedef jbooleanArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetBooleanArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetBooleanArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jchar> : public JavaObject {
	typedef jchar Elem;
	typedef jcharArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetCharArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetCharArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jbyte> : public JavaObject {
	typedef jbyte Elem;
	typedef jbyteArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetByteArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetByteArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jshort> : public JavaObject {
	typedef jshort Elem;
	typedef jshortArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetShortArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetShortArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jint> : public JavaObject {
	typedef jint Elem;
	typedef jintArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetIntArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetIntArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jlong> : public JavaObject {
	typedef jlong Elem;
	typedef jlongArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetLongArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetLongArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jfloat> : public JavaObject {
	typedef jfloat Elem;
	typedef jfloatArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetFloatArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetFloatArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<jdouble> : public JavaObject {
	typedef jdouble Elem;
	typedef jdoubleArray Arr;
public:
	JavaArray() : JavaObject() {}
	JavaArray(JavaEnv env, jsize size) : JavaObject(env, env.Val()->NewIntArray(size)) {}
	JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaArray(env, val.size()) {
		SetData(0, val.size(), &val[0]);
	}
	JavaArray(JavaEnv env, Arr a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, jsize len) {
		return JavaArray(env, len);
	};

	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr) {
		return JavaArray(env, arr);
	}

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		Elem res;
		GetData(n, 1, &res);
		return res;
	}

	void Set(jsize n, Elem val) {
		SetData(n, 1, &val);
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		GetData(0, len, &res[0]);
		return res;
	}

private:
	void GetData(jsize from, jsize len, Elem * ptr) const {
		_env.Val()->GetDoubleArrayRegion(Val(), from, len, ptr);
	}

	void SetData(jsize from, jsize len, const Elem * ptr) {
		_env.Val()->SetDoubleArrayRegion(Val(), from, len, ptr);
	}
};

template<>
class JavaArray<JavaObject> : public JavaObject {
	typedef JavaObject Elem;
	typedef jobjectArray Arr;
public:
	JavaArray() : JavaObject() {}
	// JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
	// 	FromVector(val);
	// }
	JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}
	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		return JavaObject(_env.Val(), _env.Val()->GetObjectArrayElement(Val(), n));
	}

	void Set(jsize n, const Elem& val) {
		_env.Val()->SetObjectArrayElement(Val(), n, val.Val());
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		for(jsize i = 0; i < len; ++i)
			res[i] = Get(i);
		return res;
	}

private:
	void FromVector(const std::vector<Elem>& vec) {
		jsize len = vec.size();
		for(jsize i = 0; i < len; ++i)
			Set(i, vec[i]);
	}
};

template<>
class JavaArray<JavaString> : public JavaObject {
	typedef JavaString Elem;
	typedef jobjectArray Arr;
public:
	JavaArray() : JavaObject() {}
	// JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
	// 	FromVector(val);
	// }
	JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}
	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		return JavaString(_env.Val(), (jstring) _env.Val()->GetObjectArrayElement(Val(), n));
	}

	void Set(jsize n, const Elem& val) {
		_env.Val()->SetObjectArrayElement(Val(), n, val.Val());
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		for(jsize i = 0; i < len; ++i)
			res[i] = Get(i);
		return res;
	}

private:
	void FromVector(const std::vector<Elem>& vec) {
		jsize len = vec.size();
		for(jsize i = 0; i < len; ++i)
			Set(i, vec[i]);
	}
};

template<typename T>
class JavaArray<JavaArray<T>> : public JavaObject {
	typedef JavaArray<T> Elem;
	typedef jobjectArray Arr;
public:
	JavaArray() : JavaObject() {}
	// JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
	// 	FromVector(val);
	// }
	JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}
	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		return JavaArray<T>(_env.Val(), (jarray) _env.Val()->GetObjectArrayElement(Val(), n));
	}

	void Set(jsize n, const Elem& val) {
		_env.Val()->SetObjectArrayElement(Val(), n, val.Val());
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		for(jsize i = 0; i < len; ++i)
			res[i] = Get(i);
		return res;
	}

private:
	void FromVector(const std::vector<Elem>& vec) {
		jsize len = vec.size();
		for(jsize i = 0; i < len; ++i)
			Set(i, vec[i]);
	}
};

template<>
class JavaArray<std::string> : public JavaObject {
	typedef std::string Elem;
	typedef jobjectArray Arr;
public:
	JavaArray() : JavaObject() {}
	// JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
	// 	FromVector(val);
	// }
	JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}
	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		return JavaString(_env.Val(), (jstring) _env.Val()->GetObjectArrayElement(Val(), n)).Value();
	}

	void Set(jsize n, const Elem& val) {
		// TODO: check if refcnt++ needed
		_env.Val()->SetObjectArrayElement(Val(), n, JavaString(_env.Val(), val.c_str()).Val());
	}

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		for(jsize i = 0; i < len; ++i)
			res[i] = Get(i);
		return res;
	}

private:
	void FromVector(const std::vector<Elem>& vec) {
		jsize len = vec.size();
		for(jsize i = 0; i < len; ++i)
			Set(i, vec[i]);
	}
};

template<typename T>
class JavaArray<std::vector<T>> : public JavaObject {
	typedef std::vector<T> Elem;
	typedef jobjectArray Arr;
public:
	JavaArray() : JavaObject() {}
	// JavaArray(JavaEnv env, const std::vector<Elem>& val) : JavaObject(env, env.Val()->NewObjectArray(val.size())) {
	// 	FromVector(val);
	// }
	JavaArray(JavaEnv env, jarray a) : JavaObject(env, a) {}
	JavaArray(const JavaArray& a) : JavaObject(a) {}
	JavaArray(JavaArray&& a) : JavaObject(a) {}

	static JavaArray New(JavaEnv env, const char * str);
	static JavaArray New(JavaEnv env, const std::string& str);

	virtual ~JavaArray() {}

	using JavaObject::operator=;
	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const {
		if(JavaObject::operator==(arr))
			return true;

		jsize l1 = Length(), l2 = arr.Length();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr.ToVector();
	}

	bool operator!=(const JavaArray& arr) const {
		return !(*this == arr);
	}

	bool operator==(const std::vector<Elem>& arr) const {
		jsize l1 = Length(), l2 = arr.size();
		if(l1 != l2)
			return false;
		
		return ToVector() == arr;
	}

	bool operator!=(const std::vector<Elem>& arr) const {
		return !(*this == arr);
	}

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const {
		return JavaArray<T>(_env.Val(), (jarray) _env.Val()->GetObjectArrayElement(Val(), n)).ToVector();
	}

	// TODO!
	// void Set(jsize n, const Elem& val) {
	// 	_env.Val()->SetObjectArrayElement(Val(), n, val.Val());
	// }

	// TODO: operator[]

	Elem operator[](jsize n) const { return Get(n); }

	jsize Length() const {
		return _env.Val()->GetArrayLength(Val());
	}

	Arr Val() const { return (Arr) _obj; }

	std::vector<Elem> ToVector() const {
		jsize len = Length();
		std::vector<Elem> res(len);
		for(jsize i = 0; i < len; ++i)
			res[i] = Get(i);
		return res;
	}

private:
	void FromVector(const std::vector<Elem>& vec) {
		jsize len = vec.size();
		for(jsize i = 0; i < len; ++i)
			Set(i, vec[i]);
	}
};

}

#endif
