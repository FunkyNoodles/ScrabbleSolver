#include "gtest/gtest.h"
#include "../Scrabble/Trie.h"

TEST(Trie, insertAndReadCorrect) {
	Trie trie;
	
	trie.insert("POD");
	trie.insert("PODAGRA");

	trie.insert("VEALED");
	trie.insert("VEAL");

	EXPECT_EQ(trie.find("VEAL"), true);
	EXPECT_EQ(trie.find("POD"), true);
	EXPECT_EQ(trie.find("PODAGRA"), true);
	EXPECT_EQ(trie.find("VEALED"), true);
	EXPECT_EQ(trie.find("VEALE"), false);
	EXPECT_EQ(trie.find("PODA"), false);
	EXPECT_EQ(trie.find("TEST"), false);

}

TEST(Trie, insertInvalidWordShouldThrow) {
	Trie trie;

	EXPECT_THROW(trie.insert("VeALED"), std::out_of_range);
}