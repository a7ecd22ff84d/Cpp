EnumMapper
===============================================================================

Motivation: I wanted to check if it is possible to map an enumeration to a
string and back at compile time. Generally yes, but the provided solution has
some drawbacks related to conxtexpr limitations in C++17.

Not really a project, it's more like a test to learn how constexpr
works and what are the limitations of this feature.

Usage
*******************************************************************************

.. code-block:: cpp

    // An example enum
    enum class TestEnum { Red, Blue, Green };

    // Create mapper as inline variable in header
    // Likely right after enum 
    inline constexpr auto mapper = Containers::EnumMapper<TestEnum, 3>{{{
        {TestEnum::Red, "Red"},
        {TestEnum::Blue, "Blue"},
        {TestEnum::Green, "Green"}}}};
    
    // Usage in code
    void foo()
    {
        auto str = mapper.toString(TestEnum::Red);
        auto enum = mapper.toEnum("Red");
    }

Notes
*******************************************************************************

Need to set number of enum values in template parameter
    The mapper uses an array to store a list of values, requiring you to
    explicitly provide the number of elements. I couldn't use vector because
    C++17 doesn't support it in constexpr. I also tried some tricks with an
    initializer list, a separate builder and so on, unfortunately none of that
    worked.

Does not check if all enum values were added to mapper.
    The compiler does not warn the user when not all enumeration values are
    registered in the mapper (as is the case with switch / case). There is one
    trick for this, mentioned here
    https://taylorconor.com/blog/enum-reflection/, is used in the MaginEnum
    library. I didn't want to use it here.

Notes for C++20
*******************************************************************************

Simplify initialization
    C++20 added support for vector in consexpr so it will be possible to remove
    number of items and one of braces from initializer.

Improve memory layout
    This is an overkill for this project but I want to this anyway :)
    I'd like to check if it possible to layout mapping data in two tables:
    `enum_value->pointer_to_string` and `string->enum_value` and use this
    tables to search for correct value.
    It will be possible to use binary search when data in tables will be in
    correct order. It will not affect calculations at compile time, but may
    affect values calculated at runtime. 