#include "orphan.hpp"
#include "gtest/gtest.h"

TEST(removeFrontSpacesTests, doNotRemoveAnythingWhenEmptyString) {
    std::string argument("");
    std::string expected(argument);
    removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeFrontSpacesTests, doNotRemoveAnythingWhenNoFrontSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeFrontSpacesTests, canRemoveOneFrontSpace) {
    std::string argument(1, ' ');
    argument.append("some text");
    std::string expected("some text");
    removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeFrontSpacesTests, canRemoveTwoFrontSpaces) {
    std::string argument(2, ' ');
    argument.append("some text");
    std::string expected("some text");
    removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeFrontSpacesTests, canRemoveTenFrontSpaces) {
    std::string argument(10, ' ');
    argument.append("some text");
    std::string expected("some text");
    removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}

TEST(removeSpacesOnTheEndTests, doNotRemoveAnythingWhenEmptyString) {
    std::string argument("");
    std::string expected(argument);
    removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeSpacesOnTheEndTests, doNotRemoveAnythingWhenNoEndlineSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeSpacesOnTheEndTests, canRemoveASingleEndlineSpace) {
    std::string argument("some text ");
    std::string expected("some text");
    removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeSpacesOnTheEndTests, canRemoveTwoEndlineSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    std::string spaces(2, ' ');
    argument.append(spaces);
    removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeSpacesOnTheEndTests, canRemoveTenEndlineSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    std::string spaces(10, ' ');
    argument.append(spaces);
    removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}

TEST(removeMultipleSpacesTests, doNothingWhenEmptyStringPassedIn) {
    std::string argument("");
    std::string expected("");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixAFirstDoubleSpace) {
    std::string argument("some  text");
    std::string expected("some text");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixAFirstDoubleSpaceOnTheFront) {
    std::string argument("  some text");
    std::string expected(" some text");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixADoubleSpaceOnTheEnd) {
    std::string argument("some text  ");
    std::string expected("some text ");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixAFirstTripleSpace) {
    std::string argument("some   text");
    std::string expected("some text");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixAFirstTenSpaceGap) {
    std::string spaces(10, ' ');
    std::string argument("some");
    argument.append(spaces + "text");
    std::string expected("some text");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixTwoMulticharGaps) {
    std::string argument("some  weird   text passed  in");
    std::string expected("some weird text passed in");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST(removeMultipleSpacesTests, canFixThreeMulticharGaps) {
    std::string argument("  some weird text   passed          in");
    std::string expected(" some weird text passed in");
    removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}

TEST(insertHardspacesAfterOrphansTests, canHandleFirstOrphan) {
    std::string argument("he gave me quite a weird text!");
    std::string expected("he gave me quite a~weird text!");
    insertHardspacesAfterOrphans(argument);
    EXPECT_EQ(expected, argument);
}
TEST(insertHardspacesAfterOrphansTests, canHandleTwoOrphans) {
    std::string argument("be c de f gie");
    std::string expected("be c~de f~gie");
    insertHardspacesAfterOrphans(argument);
    EXPECT_EQ(expected, argument);
}
TEST(insertHardspacesAfterOrphansTests, canHandleThreeOrphans) {
    std::string argument("ha i jot k el m en");
    std::string expected("ha i~jot k~el m~en");
    insertHardspacesAfterOrphans(argument);
    EXPECT_EQ(expected, argument);
}

TEST(insertHardspacesAfterSurnamesTests, doNothingWhenNoSpacesPassedIn) {
    std::string argument("Elephant");
    std::string expected("Elephant");
    insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
TEST(insertHardspacesAfterSurnamesTests, insertHardSpaceAfterFirstSurname) {
    std::string argument(" Zak J. abc def g ");
    std::string expected(" Zak~J. abc def g ");
    insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
TEST(insertHardspacesAfterSurnamesTests, insertHardspaceAfterTwoSurnames) {
    std::string argument(" Moniuszko A., Dunaj J. abc def g ");
    std::string expected(" Moniuszko~A., Dunaj~J. abc def g ");
    insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
TEST(insertHardspacesAfterSurnamesTests, insertHardspaceAfterThreeSurnames) {
    std::string argument(" Moniuszko A., Dunaj J., Biegus R. abc def g ");
    std::string expected(" Moniuszko~A., Dunaj~J., Biegus~R. abc def g ");
    insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
