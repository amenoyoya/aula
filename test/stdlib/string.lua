local text = "✅ hello, 世界♥"
assert(text:u8len() == 12)
assert(text:len() == 20)
printf("text: %s\nlength: %d\nbytes: %d\n", text, text:u8len(), text:len())
