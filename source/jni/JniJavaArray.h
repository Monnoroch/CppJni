#pragma once
#ifndef JNI_JAVA_ARRAY_H
#define JNI_JAVA_ARRAY_H

#include <JniForwards.h>
#include <JniJavaObject.h>
#include <JniProxy.h>


namespace JNI {

template<>
class JavaArray<jboolean> : public JavaObject {
	typedef jboolean Elem;
	typedef jbooleanArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jchar> : public JavaObject {
	typedef jchar Elem;
	typedef jcharArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jbyte> : public JavaObject {
	typedef jbyte Elem;
	typedef jbyteArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jshort> : public JavaObject {
	typedef jshort Elem;
	typedef jshortArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jint> : public JavaObject {
	typedef jint Elem;
	typedef jintArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jlong> : public JavaObject {
	typedef jlong Elem;
	typedef jlongArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jfloat> : public JavaObject {
	typedef jfloat Elem;
	typedef jfloatArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<jdouble> : public JavaObject {
	typedef jdouble Elem;
	typedef jdoubleArray Arr;
public:
	JavaArray();
	JavaArray(JavaEnv env, jsize size);
	JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, Arr a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);

	static JavaArray New(JavaEnv env, jsize len);
	static JavaArray New(JavaEnv env, const std::vector<Elem>& arr);

	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, Elem val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void GetData(jsize from, jsize len, Elem * ptr) const;
	void SetData(jsize from, jsize len, const Elem * ptr);
};

template<>
class JavaArray<JavaObject> : public JavaObject {
	typedef JavaObject Elem;
	typedef jobjectArray Arr;
public:
	JavaArray();
	// JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, jarray a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);
	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, const Elem& val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void FromVector(const std::vector<Elem>& vec);
};

template<>
class JavaArray<JavaString> : public JavaObject {
	typedef JavaString Elem;
	typedef jobjectArray Arr;
public:
	JavaArray();
	// JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, jarray a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);
	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, const Elem& val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void FromVector(const std::vector<Elem>& vec);
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

	JavaArray& operator=(const JavaArray& arr) {
		JavaObject::operator=(arr);
		return *this;
	}

	JavaArray& operator=(JavaArray&& arr) {
		JavaObject::operator=(std::move(arr));
		return *this;
	}

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
		return FromJavaProxy<Elem>(_env, _env.Val()->GetObjectArrayElement(Val(), n)).Val();
	}

	void Set(jsize n, const Elem& val) {
		_env.Val()->SetObjectArrayElement(Val(), n, ToJavaProxy<Elem>(_env, val).Val());
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
	JavaArray();
	// JavaArray(JavaEnv env, const std::vector<Elem>& val);
	JavaArray(JavaEnv env, jarray a);
	JavaArray(const JavaArray& a);
	JavaArray(JavaArray&& a);
	virtual ~JavaArray();

	JavaArray& operator=(const JavaArray& arr);
	JavaArray& operator=(JavaArray&& arr);

	using JavaObject::operator==;
	using JavaObject::operator!=;

	bool operator==(const JavaArray& arr) const;
	bool operator!=(const JavaArray& arr) const;
	bool operator==(const std::vector<Elem>& arr) const;
	bool operator!=(const std::vector<Elem>& arr) const;

	friend bool operator==(const std::vector<Elem>& arr, const JavaArray& self) {
		return self == arr;
	}

	friend bool operator!=(const std::vector<Elem>& arr, const JavaArray& self) {
		return self != arr;
	}

	Elem Get(jsize n) const;
	void Set(jsize n, const Elem& val);

	// TODO: operator[]

	Elem operator[](jsize n) const;

	jsize Length() const;
	Arr Val() const;

	std::vector<Elem> ToVector() const;

private:
	void FromVector(const std::vector<Elem>& vec);
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

	JavaArray& operator=(const JavaArray& arr) {
		JavaObject::operator=(arr);
		return *this;
	}

	JavaArray& operator=(JavaArray&& arr) {
		JavaObject::operator=(std::move(arr));
		return *this;
	}

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
		return FromJavaProxy<Elem>(_env, _env.Val()->GetObjectArrayElement(Val(), n)).Val();
	}

	// TODO!
	void Set(jsize n, const Elem& val) {
		_env.Val()->SetObjectArrayElement(Val(), n, ToJavaProxy<Elem>(_env, val).Val());
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

}

#endif
