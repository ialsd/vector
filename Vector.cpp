#include "Vector.h"

Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    _size = size;
	_capacity = size;
    _multiplicativeCoef = coef;
	_data = new Value[_size];
    for (size_t i = 0; i < size; i++) //
        {
            _data[i] = rawArray[i];
        }
}

Vector::Vector(const Vector& other)
{
    if (this != &other) 
    {
        delete[] _data;
        _data = new Value[other._size];
        for (size_t i = 0; i < other._size; ++i) 
            {
                _data[i] = other._data[i];
            }
        _size = other._size;
        _capacity = other._size; //
	_multiplicativeCoef = other._multiplicativeCoef;
    }
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        delete[] _data;
        _data = new Value[other._size]; //
        for (size_t i = 0; i < other._size; ++i) 
            {
                _data[i] = other._data[i];
            }
        _size = other._size;
        _capacity = other._size; //
	_multiplicativeCoef = other._multiplicativeCoef;
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
        _data = other._data;
        _size = other._size;
        _capacity = other._size;
        other._data = nullptr;
        other._size = other._capacity = 0;
	_multiplicativeCoef = other._multiplicativeCoef;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other) 
    {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._size;
        other._data = nullptr;
        other._size = other._capacity = 0;
	_multiplicativeCoef = other._multiplicativeCoef;
    }
    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::pushBack(const Value& value)
{
    insert(&value, 1, _size);
}

void Vector::pushFront(const Value& value)
{
    insert(&value, 1, 0);
}

void Vector::insert(const Value& value, size_t pos)
{
    insert(&value, 1, pos);
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    if (_size + size > _capacity)
    {
	size_t tmp = _capacity;
        if (tmp == 0)
        {
            tmp = 1*_multiplicativeCoef;
        }
        while (_size + size > tmp)
            {
                tmp *= _multiplicativeCoef;
            }
        reserve(tmp);
    }
    for (int i = _size + size - 1, j = size - 1; i >= pos; i--)
        {
            if (pos + size < i)
            {
                _data[i] = _data[i - size];
            }
            else
            {
                _data[i] = values[j];
                j--;                    
            }
        }
    _size = _size + size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

void Vector::popBack()
{
    erase(_size - 1);
}

void Vector::popFront()
{
    erase(0);
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size)
	{
	    return;
	}
    if (_size > 0)
    {
        if (pos + count > _size)
        {
            count = _size - pos;
        }
        size_t k = 0;
        for (size_t i = 0; i < _size; i++)
            {
                if (i < pos || i >= pos + count)
                {
                    _data[k] = _data[i];
                    k++;
                }
            }
        _size -= count;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (beginPos > _size || beginPos >= endPos)
    {
        cout << "error";
    }
    else
    {
        erase(beginPos, endPos - beginPos);
    }
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    return double(_size) / double(_capacity);
}

Value& Vector::operator[](size_t idx)
{
    return _data[idx];
}
const Value& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

long long Vector::find(const Value& value) const
{
    for (size_t i = 0; i < _size; i++)
        {
            if(_data[i] == value)
            {
                return i;
            }
        }
    return -1;
}

void Vector::reserve(size_t capacity)
{
	if (capacity > _capacity)
            {
                _capacity = capacity;
                
		if(_capacity == 0) {
			_data = nullptr;
		}
		if(_data == nullptr) {
			_data = new Value[_capacity];
			return;
		}
        	Value* newData = new Value[_capacity];
	for(auto i = 0; i < _size; i++) {
		newData[i] = _data[i];
	}
	delete[] _data;
	_data = newData;
	    }
}

void Vector::shrinkToFit()
{
    _capacity = _size;
    Value* tmp = _data;
    _data = new Value[_capacity];
    for (size_t i = 0; i < _size; i++)
         {
             _data[i] = tmp[i];
         }
     delete[] tmp;
}

Vector::Iterator::Iterator(Value* ptr)
{
    _ptr = ptr;
}

Value& Vector::Iterator::operator*()
{
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const
{
    return *_ptr;
}

Value* Vector::Iterator::operator->()
{
    return _ptr;
}

const Value* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    ++_ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Vector::Iterator tmp(_ptr);
    ++_ptr;
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin()
{
    return Vector::Iterator(_data);
}
Vector::Iterator Vector::end()
{
    return Vector::Iterator(_data + _size);
}
