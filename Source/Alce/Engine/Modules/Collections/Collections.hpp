#pragma once

#include <vector>
#include <map>
#include "../Exceptions/Exceptions.hpp"
#include <algorithm>
#include <set>
#include <functional>

namespace alce
{
	template<typename T>
	class List
	{
	public:

	    using CompareFunction = std::function<bool(const T&, const T&)>;

		List()
		{

		}

		List(std::initializer_list<T> in_list) : vector(in_list)
		{
			
		}

		List(std::vector<T> vector) : vector(std::move(vector))
		{
			
		}

		List<T>& Add(const T& element)
		{
			vector.push_back(element);

			return *this;
		}

		List<T>& AddFirst(const T& element)
		{
			vector.insert(vector.begin(), element);

			return *this;
		}

		List<T>& SetFirst(size_t index)
		{
			if (index >= this->Length()) 
			{
            	throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::MoveToFront(size_t index)\n<!> Reason -> Index out of bounds");
			}

        	T element = vector[index];
        	vector.erase(vector.begin() + index);
        	vector.insert(vector.begin(), element);

			return *this;
		}

		List<T>& PopFirst()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::PopFirst()\n<!> Reason -> Empty list");

			this->vector.erase(this->vector.begin());

			return *this;
		}

		List<T>& PopLast()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::PopLast()\n<!> Reason -> Empty list");

			vector.pop_back();

			return *this;
		}

		T& Last()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::Last()\n<!> Reason -> Empty list");

			return vector.back();
		}

		T& First()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::First()\n<!> Reason -> Empty list");

			return vector[0];
		}

		List<T>& Clear()
		{
			vector.clear();

			return *this;
		}

		T& Get(size_t index)
		{
			if (index > this->Length() - 1) 
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::Get(size_t index)\n<!> Reason -> Index out of bounds");

			return vector[index];
		}

		List<T>& Set(size_t index, const T& value)
		{
			if (index >= vector.size()) 
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::Set(size_t index, T value)\n<!> Reason -> Index out of bounds");

			vector[index] = value;

			return *this;
		}

		size_t Length()
		{
			return vector.size();
		}

		template<typename Predicate>
		List<T> Filter(Predicate condition)
		{
			List<T> result = {};

			for (const T& element : vector)
			{
				if (condition(element))
				{
					result.Add(element);
				}
			}
			
			return result;
		}

		int FindIndex(const T& element)
		{
			for (size_t i = 0; i < this->vector.size(); i++)
			{
				if (vector[i] == element) return i;
			}

			return -1;
		}

		List<T>& FindAndRemove(const T& element)
		{
			auto it = std::find(vector.begin(), vector.end(), element);
			if (it != vector.end())
			{
				vector.erase(it);
			}

			return *this;
		}

		List<T>& RemoveIndex(unsigned int index)
		{
			vector.erase(vector.begin() + index);

			return *this;
		}

		template<typename Predicate>
		List<T>& RemoveIf(Predicate condition)
		{
			vector.erase(std::remove_if(vector.begin(), vector.end(), condition), vector.end());
			
			return *this;
		}

		List<T>& Sort(CompareFunction compare)
	    {
        	std::sort(vector.begin(), vector.end(), compare);
			
			return *this;
    	}

		List<T>& Merge(List<T> other)
		{
			for (const T& element : other.vector)
			{
				if (!this->Contains(element))
				{
					this->Add(element);
				}
			}

			return *this;
		}

		template<typename Func>
		List<T>& ForEach(Func func)
		{
			for(auto& element : vector)
			{
				func(element);
			}

			return *this;
		}

		bool Contains(const T& element)
		{
			return std::find(vector.begin(), vector.end(), element) != vector.end();
		}

		bool Empty()
		{
			return this->Length() == 0;
		}

		std::vector<T> ToStdVector()
		{
			return vector;
		}

		std::vector<T>* ToStdVectorPtr()
		{
			return &vector;
		}

		void operator=(std::initializer_list<T> in_list)
		{
			this->vector = in_list;
		}

		void operator=(std::vector<T> vector)
		{
			this->vector = vector;
		}

		T operator[](size_t index)
		{
			if (index > this->Length() - 1) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::operator[](size_t index)\n<!> Reason -> Index out of bounds");

			return vector[index];
		}

		void operator<<(T element)
		{
			vector.push_back(element);
		}

		std::vector<T> operator~()
		{
			return vector;
		}

		//Iteration stuff

		typedef T* iterator;
        typedef const T* const_iterator;

		iterator begin()
        {
            return vector.data();
        }

        iterator end()
        {
            return vector.data() + vector.size();
        }

        const_iterator begin() const
        {
            return vector.data();
        }

        const_iterator end() const
        {
            return vector.data() + vector.size();
        }

        const_iterator cbegin() const
        {
            return vector.data();
        }

        const_iterator cend() const
        {
            return vector.data() + vector.size();
        }

	protected:

		std::vector<T> vector = {};
	};

	template<typename F, typename S>
	class Pair
	{
	public:

		Pair()
		{

		}

		Pair(F first, S second)
		{
			this->first = first;
			this->second = second;
		}

		void operator=(std::pair<F, S> pair)
		{
			first = pair.first;
			second = pair.second;
		}

		F first;
		S second;
	};

	template<typename K, typename V>
	class Dictionary
	{
	public:

		Dictionary()
		{

		}

		Dictionary(std::initializer_list<std::pair<K, V>> map)
		{
			for (const std::pair<K, V>* it = map.begin(); it != map.end(); ++it)
			{
				list.Add(Pair<K, V>(it->first, it->second));
			}
		}

		std::vector<Pair<K, V>> std_vector()
		{
			return ~list;
		}

		size_t Length()
		{
			return list.Length();
		}

		V Get(K key)
		{
			for (int i = 0; i < list.Length(); i++)
			{
				if (list[i].first == key)
				{
					return list[i].second;
				}
			}

			throw exception::collections::NotFoundKeyException("<?> Here -> alce::Dictionary::Get(K key)\n<!> Reason -> Key not found in the dictionary");
		}

		void Set(K key, V value)
		{
			for (int i = 0; i < list.Length(); i++)
			{
				if (list[i].first == key)
				{
					list.RemoveIndex(i);
					list.Add(Pair<K, V>(key, value));
					return;
				}
			}

			list.Add(Pair<K, V>(key, value));
		}

		void RemoveByKey(K key)
		{
			for (int i = 0; i < list.Length(); i++)
			{
				if (list[i].first == key)
				{
					list.RemoveIndex(i);
					return;
				}
			}
		}

		void RemoveByValue(V value)
		{
			for (int i = 0; i < list.Length(); i++)
			{
				if (list[i].second == value)
				{
					list.RemoveIndex(i);
				}
			}
		}

		void Clear()
		{
			list.Clear();
		}

		List<K> GetKeyList()
		{
			List<K> key_list;

			for(auto& i: list)
			{
				key_list.Add(i.first);
			}

			return key_list;
		}

		List<V> GetValueList()
		{
			List<V> value_list;

			for (int i = 0; i < list.Length(); i++)
			{
				value_list.Add(list[i].second);
			}

			return value_list;
		}

		Dictionary<K, V> FilterByValue(const V& value)
		{
			Dictionary<K, V> filter_dic;

			for (int i = 0; i < list.Length(); i++)
			{
				if(list[i].second == value)
				{
					filter_dic.Set(list[i].first, list[i].second);
				}
			}

			return filter_dic;
		}

		bool HasKey(const K& key)
		{
			return GetKeyList().Contains(key);
		}

		bool Empty()
		{
			return this->Length() == 0;
		}

		void operator=(std::initializer_list<std::pair<K, V>> map)
		{
			for (const std::pair<K, V>* it = map.begin(); it != map.end(); ++it)
			{
				list.Add(Pair<K, V>(it->first, it->second));
			}
		}

		bool operator==(Dictionary& d)
		{
			if (this->Length() != d.Length()) return false;

			for (int i = 0; i < list.Length(); i++)
			{
				if ((list[i].first != d.list[i].first) || (list[i].second != d.list[i].second))
				{
					return false;
				}
			}

			return true;
		}

		bool operator!=(Dictionary& d)
		{
			if (this->Length() != d.Length()) return true;

			for (int i = 0; i < list.Length(); i++)
			{
				if ((list[i].first != d.list[i].first) || (list[i].second != d.list[i].second))
				{
					return true;
				}
			}

			return false;
		}

		std::vector<Pair<K, V>> operator~()
		{
			return ~list;
		}

		V operator[](K key)
		{
			return this->Get(key);
		}

		void operator+=(std::pair<K, V> pair)
		{
			this->Set(pair.first, pair.second);
		}

		//Iteration stuff

		typedef typename List<Pair<K, V>>::iterator iterator;
        typedef typename List<Pair<K, V>>::const_iterator const_iterator;

        iterator begin()
        {
            return list.begin();
        }

        iterator end()
        {
            return list.end();
        }

        const_iterator begin() const
        {
            return list.begin();
        }

        const_iterator end() const
        {
            return list.end();
        }

        const_iterator cbegin() const
        {
            return list.cbegin();
        }

        const_iterator cend() const
        {
            return list.cend();
        }

	private:

		List<Pair<K, V>> list;
	};
}