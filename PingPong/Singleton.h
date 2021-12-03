#pragma once

class Singleton
{
public:
	class INode { }; 

private:
	template <typename T>
	class Holder 
	{
	private:
		static T* Instance;

	public:
		static void SetInstance(T* instance)
		{
			if (Instance != nullptr)
				assert(false && "mInstance != nullptr");

			Instance = instance;
		}

		static T* GetInstance()
		{
			return Instance;
		}

		static bool HasInstance()
		{
			return Instance != nullptr;
		}
	};

public:
	template <typename T>
	static T& Get()
	{
		return Holder<T>::GetInstance();
	}

	template <typename T>
	static bool Exists()
	{
		return Holder<T>::HasInstance();
	}

	template <typename T>
	static void Register(T* instance)
	{
		static_assert(true == std::is_convertible<T, INode>::value, "only register (INode)");
		Holder<T>::SetInstance(instance);
	}

	template <typename T>
	static void Register()
	{
		Register(new T);
	}
};


template <typename T>
T* Singleton::Holder<T>::Instance = nullptr;
