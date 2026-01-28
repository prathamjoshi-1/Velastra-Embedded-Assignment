## 📘 Stack Implementation in C (Sensor Error Codes)

🧭 Overview

This project focuses on implementing a robust, non-recursive stack data structure in C using a linked list. The stack is specifically designed to store sensor error codes in embedded or low-level systems where memory control, predictability, and reliability are critical.

A special circular behavior is implemented to handle stack overflow gracefully by overwriting the oldest entry.


---

🧩 Problem Statement

Design and implement a stack in C using a linked list that can store sensor error codes. The stack must operate without recursion, enforce a fixed maximum size, and safely handle overflow conditions.


---

⚙️ Technical Requirements

🧱 Data Structure

Stack implemented using a linked list

Each node represents a sensor error code

No recursive logic is allowed


📏 Constraints

🔢 Maximum Stack Size: 32 nodes

🚫 Stack growth beyond this limit must not crash the system



---

🔧 Supported Operations

⬆️ Push Operation

Add a new error code to the top of the stack

If the stack is full:

🔄 Automatically overwrite the oldest entry (circular stack behavior)



⬇️ Pop Operation

Remove and return the most recent error code

Handle underflow conditions safely



---

🔄 Special Overflow Behavior (Circular Stack)

When the stack reaches its maximum capacity:

The oldest node (bottom of the stack) is removed

The new error code is pushed onto the top

Stack size remains constant at 32


This ensures:

No memory overflow

Continuous logging of the most recent error events



---

🛡️ Error Handling

The implementation must properly handle:

Stack underflow (pop on empty stack)

Stack overflow (handled via circular overwrite logic)

Memory allocation failures


All error conditions should:

Be safely handled

Return meaningful status codes or messages



---

🧠 Design Considerations

Clean and readable code structure

Clear separation of concerns:

Stack initialization

Push logic

Pop logic

Overflow handling


No global state abuse

Efficient memory usage



---

📝 Code Quality Expectations

Meaningful variable and function names

Proper inline comments explaining logic

Consistent formatting and indentation

Defensive programming practices



---

💻 Programming Language

✅ Language: C

📚 Standard C libraries only

Suitable for embedded and low-level system environments



---

📦 Expected Outcome

By completing this implementation, you will demonstrate:

Strong understanding of linked list–based stacks

Practical handling of fixed-size constraints

Ability to design safe overflow mechanisms

Readable and maintainable C code suitable for production



---

🚀 Typical Use Cases

Embedded error logging systems

Sensor fault tracking

Circular event buffers

Low-memory environments



---

✅ Conclusion

This stack implementation reflects real-world embedded system needs where memory limits and reliability matter more than theoretical flexibility. The circular overwrite mechanism ensures continuous operation without failure, making it ideal for sensor error tracking and diagnostics.


---

📌 Designed with embedded-system best practices in mind.