#include "gtest/gtest.h"
#include "../Scrabble/Trie.h"
#include "../Scrabble/TrieTracker.h"

class TrieTest : public ::testing::Test {
protected:
	Trie * trie;
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
	TrieTracker * tracker = new TrieTracker(*trie);
	EXPECT_EQ(tracker->next('X'), false);
	tracker->next('V');
	tracker->next('E');
	tracker->next('A');
	EXPECT_EQ(tracker->isCurStateWord(), false);
	tracker->next('L');
	EXPECT_EQ(tracker->isCurStateWord(), true);
	tracker->next('E');
	EXPECT_EQ(tracker->isCurStateWord(), false);
	tracker->prev();
	EXPECT_EQ(tracker->isCurStateWord(), true);
	tracker->resetState();
	tracker->prev();
	EXPECT_EQ(tracker->next('X'), false);
	EXPECT_EQ(tracker->next('V'), true);
	EXPECT_EQ(tracker->isCurStateWord(), false);
}
