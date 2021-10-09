# Debugging unit test failures

The unit tests are based on using `pdftotext` to generate an out and use that as the
reference data set.

Use the library to also generate an output and diff the two.
The results should be identical

One thing I found useful was to print out the string data as hex characters

```cpp
std::string data;


inline unsigned int to_uint(char ch)
{
  return static_cast<unsigned int>(static_cast<unsigned char>(ch));
}

for (const char &ch : data)
{
  cout << "0x" << std::hex << to_uint(ch) << ' ';
}
```
