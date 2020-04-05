#include <string>
#include <sstream>
#include <list>

#include "test_runner.h"

using namespace std;

class Editor {
public:
	// Реализуйте конструктор по умолчанию и объявленные методы
	Editor();
	void Left();
	void Right();
	void Insert(char token);
	void Cut(size_t tokens = 1);
	void Copy(size_t tokens = 1);
	void Paste();
	string GetText() const;
	
private:
	list<char>::iterator MovePosition(size_t tokens = 1); 
	
private:
	list<char> text;
	list<char>::iterator cursor_pos;
	list<char> buffer;  
};

Editor::Editor():
	cursor_pos(text.begin())
{
}

list<char>::iterator Editor::MovePosition(size_t tokens) {
	list<char>::iterator res_pos = cursor_pos;
	
	size_t i = 0;
	while( (i < tokens) && (res_pos != text.end()) ){
		res_pos++;
		i++;
	}

	return res_pos;
}

void Editor::Left() {
	if (cursor_pos != text.begin()) {
		cursor_pos--;
	}
}

void Editor::Right() {
	if (cursor_pos != text.end()) {
		cursor_pos++;
	}
}

void Editor::Insert(char token) {
	text.insert(cursor_pos, token);
}

void Editor::Cut(size_t tokens) {
	buffer.clear();
	list<char>::iterator res_pos = MovePosition(tokens);
	buffer.splice(buffer.begin(), text, cursor_pos, res_pos);
	cursor_pos = res_pos;
}

void Editor::Copy(size_t tokens) {
	buffer.assign(cursor_pos, MovePosition(tokens));
}

void Editor::Paste() {
	text.insert(cursor_pos, buffer.begin(), buffer.end());
}

string Editor::GetText() const {
	ostringstream os;
	
	for (auto it = text.begin(); it != text.end(); ++it) {
		os << *it;
	}
	
	return os.str();
}

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
