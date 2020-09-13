#include "Orphan.hpp"
#include "gtest/gtest.h"

struct removeFrontSpacesTests : public ::testing::Test {
    Orphan myOrphan{};
};
TEST_F(removeFrontSpacesTests, doNotRemoveAnythingWhenEmptyString) {
    std::string argument("");
    std::string expected(argument);
    myOrphan.removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeFrontSpacesTests, doNotRemoveAnythingWhenNoFrontSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    myOrphan.removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeFrontSpacesTests, canRemoveOneFrontSpace) {
    std::string argument(1, ' ');
    argument.append("some text");
    std::string expected("some text");
    myOrphan.removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeFrontSpacesTests, canRemoveTwoFrontSpaces) {
    std::string argument(2, ' ');
    argument.append("some text");
    std::string expected("some text");
    myOrphan.removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeFrontSpacesTests, canRemoveTenFrontSpaces) {
    std::string argument(10, ' ');
    argument.append("some text");
    std::string expected("some text");
    myOrphan.removeFrontSpaces(argument);
    EXPECT_EQ(expected, argument);
}

struct removeSpacesOnTheEndTests : public removeFrontSpacesTests {};
TEST_F(removeSpacesOnTheEndTests, doNotRemoveAnythingWhenEmptyString) {
    std::string argument("");
    std::string expected(argument);
    myOrphan.removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeSpacesOnTheEndTests, doNotRemoveAnythingWhenNoEndlineSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    myOrphan.removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeSpacesOnTheEndTests, canRemoveASingleEndlineSpace) {
    std::string argument("some text ");
    std::string expected("some text");
    myOrphan.removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeSpacesOnTheEndTests, canRemoveTwoEndlineSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    std::string spaces(2, ' ');
    argument.append(spaces);
    myOrphan.removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeSpacesOnTheEndTests, canRemoveTenEndlineSpaces) {
    std::string argument("some text");
    std::string expected(argument);
    std::string spaces(10, ' ');
    argument.append(spaces);
    myOrphan.removeSpacesOnTheEnd(argument);
    EXPECT_EQ(expected, argument);
}

struct removeMultipleSpacesTests : public removeFrontSpacesTests {};
TEST_F(removeMultipleSpacesTests, doNothingWhenEmptyStringPassedIn) {
    std::string argument("");
    std::string expected("");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixAFirstDoubleSpace) {
    std::string argument("some  text");
    std::string expected("some text");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixAFirstDoubleSpaceOnTheFront) {
    std::string argument("  some text");
    std::string expected(" some text");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixADoubleSpaceOnTheEnd) {
    std::string argument("some text  ");
    std::string expected("some text ");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixAFirstTripleSpace) {
    std::string argument("some   text");
    std::string expected("some text");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixAFirstTenSpaceGap) {
    std::string spaces(10, ' ');
    std::string argument("some");
    argument.append(spaces + "text");
    std::string expected("some text");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixTwoMulticharGaps) {
    std::string argument("some  weird   text passed  in");
    std::string expected("some weird text passed in");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(removeMultipleSpacesTests, canFixThreeMulticharGaps) {
    std::string argument("  some weird text   passed          in");
    std::string expected(" some weird text passed in");
    myOrphan.removeMultipleSpaces(argument);
    EXPECT_EQ(expected, argument);
}

struct insertHardspacesAfterOrphansTests : public removeFrontSpacesTests {};
TEST_F(insertHardspacesAfterOrphansTests, canHandleFirstOrphan) {
    std::string argument("he gave me quite a weird text!");
    std::string expected("he gave me quite a~weird text!");
    myOrphan.insertHardspacesAfterOrphans(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(insertHardspacesAfterOrphansTests, canHandleTwoOrphans) {
    std::string argument("be c de f gie");
    std::string expected("be c~de f~gie");
    myOrphan.insertHardspacesAfterOrphans(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(insertHardspacesAfterOrphansTests, canHandleThreeOrphans) {
    std::string argument("ha i jot k el m en");
    std::string expected("ha i~jot k~el m~en");
    myOrphan.insertHardspacesAfterOrphans(argument);
    EXPECT_EQ(expected, argument);
}

struct insertHardspacesAfterSurnamesTests : public removeFrontSpacesTests {};
TEST_F(insertHardspacesAfterSurnamesTests, doNothingWhenNoSpacesPassedIn) {
    std::string argument("Elephant");
    std::string expected("Elephant");
    myOrphan.insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(insertHardspacesAfterSurnamesTests, insertHardSpaceAfterFirstSurname) {
    std::string argument(" Zak J. abc def g ");
    std::string expected(" Zak~J. abc def g ");
    myOrphan.insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(insertHardspacesAfterSurnamesTests, insertHardspaceAfterTwoSurnames) {
    std::string argument(" Moniuszko A., Dunaj J. abc def g ");
    std::string expected(" Moniuszko~A., Dunaj~J. abc def g ");
    myOrphan.insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
TEST_F(insertHardspacesAfterSurnamesTests, insertHardspaceAfterThreeSurnames) {
    std::string argument(" Moniuszko A., Dunaj J., Biegus R. abc def g ");
    std::string expected(" Moniuszko~A., Dunaj~J., Biegus~R. abc def g ");
    myOrphan.insertHardSpacesAfterSurnames(argument);
    EXPECT_EQ(expected, argument);
}
