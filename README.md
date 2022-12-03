# Warning
Ampersand is currently in "Experimental" state, and most of feature is unstable. <br>
Do not use this library at actual development process, until all feature become stable.
<br>
<br>

# 1. Introduction
"Ampersand" is library that enables user to create meta - data type, and import and export various data formats with that meta - type.<br>
User can define "format" of the type with meta - data type, use the format (meta - data type) to fetch same data format which is stored with various data format, like JSON or MariaDB.<br><br>

For example, look codes below.

<b>[C++]</b>
```
class Test
{
public:
    int a;
    int b;
    int c;
};
```

<b>[SQL]</b>
```
CREATE TABLE Test
(
    a INT,
    b INT,
    c INT
)
```

<b>[JSON]</b>
```
{
    a : 1
    b : 2
    c : 3
}
```

All of codes above describes data types which can contain three integer types. However, in conventional programming, user must multiply declare "same data type" to define that type using different format / schema language like above.<br>
Ampersand's Meta Type System can be helpful for these scenarios. Like code below, one meta type declaration can denote all of different type description above.


<b>[C++ - With Ampersand]</b>
```
using member_a = ampersand::meta::attribute<int, a_annot>;
using member_b = ampersand::meta::attribute<int, b_annot>;
using member_c = ampersand::meta::attribute<int, c_annot>;

auto meta_type = ampersand::meta::meta_type { member_a{}, member_b{}, member_c{} };
```

Ampersand's extension features, like MySQL can describe these meta type into other formats.<br>
Following code is example that how Ampersand describes and reads SQL table with ampersand::meta::meta_type.

<br>
<b>[C++ - With Ampersand]</b>

<br>

```
struct test_annotation  : ampersand::meta::annotation {};
struct test2_annotation : ampersand::meta::annotation {};

using test  = ampersand::meta::attribute<int, test_annotation> ;
using test2 = ampersand::meta::attribute<int, test2_annotation>;

ampersand::schema::table<test_meta> Table ("testtable");
ampersand::schema::syntax::select   Syntax( Table );

(... DB Connection Process ...)

ampersand::extension::mysql::parser			 Parser(Syntax);
ampersand::extension::mysql::reader			 Reader(ampersand::meta::body::raw{}, Connection, Parser);
ampersand::extension::mysql::reader_iterator ReaderIterator(Reader);

std::cout << (*ReaderIterator)[test {}] << std::endl;
std::cout << (*ReaderIterator)[test2{}] << std::endl;
```
<br>
<br>

# 2. Why Ampersand?
Ampersand does not requires any additional schema language like Google's Protobuf, only works with C++ type system.<br>
Thus who uses C++ can easily exports and imports bunch of data with using Ampersand's meta type system, not using other transpiler.

<br>
Ampersand is mostly consisted with header, and supports compile - time object creation (constexpr)
<br>
which could boost the software's performance removing unnecessary object creation / deletion process in runtime binary.