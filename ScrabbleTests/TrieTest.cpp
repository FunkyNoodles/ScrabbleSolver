#include "gtest/gtest.h"
#include "../Scrabble/Trie.h"

class TrieTest : public ::testing::Test {
protected:
	Trie *trie;
	TrieTest() {}

	virtual void SetUp() {
		trie = new Trie();
		trie->insert("POD");
		trie->insert("PODAGRA");

		trie->insert("VEALED");
		trie->insert("VEAL");
	}

	virtual void TearDown() {
		delete trie;
	}
};

TEST_F(TrieTest, insertAndReadCorrect) {
	EXPECT_EQ(trie->find("VEAL"), true);
	EXPECT_EQ(trie->find("POD"), true);
	EXPECT_EQ(trie->find("PODAGRA"), true);
	EXPECT_EQ(trie->find("VEALED"), true);
	EXPECT_EQ(trie->find("VEALE"), false);
	EXPECT_EQ(trie->find("PODA"), false);
	EXPECT_EQ(trie->find("TEST"), false);
}

TEST_F(TrieTest, insertInvalidWordShouldThrow) {

	EXPECT_THROW(trie->insert("VeALED"), std::out_of_range);
}

TEST_F(TrieTest, stateStepsCorrect) {
	EXPECT_EQ(trie->next('X'), false);
	trie->next('V');
	trie->next('E');
	trie->next('A');
	EXPECT_EQ(trie->isCurStateWord(), false);
	trie->next('L');
	EXPECT_EQ(trie->isCurStateWord(), true);
	trie->next('E');
	EXPECT_EQ(trie->isCurStateWord(), false);
	trie->prev();
	EXPECT_EQ(trie->isCurStateWord(), true);
	trie->resetState();
	trie->prev();
	EXPECT_EQ(trie->next('X'), false);
	EXPECT_EQ(trie->next('V'), true);
	EXPECT_EQ(trie->isCurStateWord(), false);
}
