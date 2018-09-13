//
// Created by Lauretta Agliata on 07/09/18.
//

#include "gtest/gtest.h"
#include "../INIManager.h"

TEST(INITest, managerTest){
    INIManager im;
    im.addSection("screen");
    EXPECT_TRUE(im.getConfiguration().find("screen") != im.getConfiguration().end());
    im.addParamToSection("full screen", "true", "screen");
    EXPECT_TRUE(im.getConfiguration().at("screen")->find("full screen") != im.getConfiguration().at("screen")->end());
    EXPECT_EQ(im.getParamValueInSection("full screen", "screen"), "true");
    im.addParamToSection("full screen", "false", "screen");
    EXPECT_EQ(im.getParamValueInSection("full screen", "screen"), "false");
    EXPECT_ANY_THROW(im.addParamToSection("section", "not", "added"));
    EXPECT_ANY_THROW(im.getCommentFromSection("screen"));
    im.addCommentToSection("this is a comment", "screen");
    EXPECT_EQ(im.getCommentFromSection("screen"), "this is a comment");
    EXPECT_ANY_THROW(im.addCommentToSection("not added section", "fake comment"));
    im.addSection("resolution");
    std::list<std::string> sections;
    sections.push_back("screen");
    EXPECT_EQ(im.findParamSection("full screen"), sections);
    EXPECT_ANY_THROW(im.findParamSection("not added param"));
    im.changeParamInSection("full screen", "true", "screen");
    EXPECT_EQ(im.getParamValueInSection("full screen", "screen"), "true");
    EXPECT_ANY_THROW(im.getParamValueInSection("not added param", "screen"));
    EXPECT_ANY_THROW(im.getParamValueInSection("full screen", "not added section"));
    im.changeSectionName("screen", "game screen");
    EXPECT_TRUE(im.getConfiguration().find("game screen") != im.getConfiguration().end());
    EXPECT_TRUE(im.getConfiguration().at("game screen")->find("full screen") != im.getConfiguration().at("game screen")->end());
    EXPECT_EQ(im.getParamValueInSection("full screen", "game scsreen"), "true");
    EXPECT_EQ(im.getCommentFromSection("game screen"), "this is a comment");
    EXPECT_ANY_THROW(im.changeSectionName("not added section", "fake section name"));
    im.changeCommentInSection("this is another comment", "game screen");
    EXPECT_EQ(im.getCommentFromSection("game screen"), "this is another comment");
    EXPECT_ANY_THROW(im.changeCommentInSection("fake new comment", "not added section"));
    im.removeParamFromSection("full screen", "game screen");
    EXPECT_TRUE(im.getConfiguration().at("screen")->find("full screen") == im.getConfiguration().at("screen")->end());
    EXPECT_ANY_THROW(im.removeParamFromSection("not added param", "game screen"));
    EXPECT_ANY_THROW(im.removeParamFromSection("full screen", "not added section"));
    im.removeCommentFromSection("game screen");
    EXPECT_ANY_THROW(im.getCommentFromSection("game screen"));
    im.removeSection("game screen");
    EXPECT_TRUE(im.getConfiguration().find("game screen") == im.getConfiguration().end());
    EXPECT_ANY_THROW(im.removeSection("not added section"));
}

TEST(INITest, IOTest){
    INIManager im;
    im.addSection("screen");
    im.addParamToSection("full screen", "true", "screen");
    im.addSection("resolution");
    im.addParamToSection("height", "1080", "resolution");
    im.addParamToSection("width", "1720", "resolution");
    im.addCommentToSection("commento a caso","screen");
    im.writeFile("configTest.ini");
    im.readFile("configTest.ini");
    EXPECT_TRUE(im.getConfiguration().find("screen") != im.getConfiguration().end());
    EXPECT_TRUE(im.getConfiguration().find("resolution") != im.getConfiguration().end());
    EXPECT_EQ(im.getParamValueInSection("full screen", "screen"), "true");
    EXPECT_EQ(im.getParamValueInSection("width", "resolution"), "1720");
    EXPECT_EQ(im.getParamValueInSection("height", "resolution"), "1080");
    EXPECT_EQ(im.getCommentFromSection("screen"), "commento a caso");

    //modifico, scrivo leggo e controllo che le modifiche ci siano ancora
    im.addSection("game option");
    im.addParamToSection("sensibility", "0.5", "game option");
    im.addParamToSection("aimbot", "true", "game option");
    im.changeSectionName("screen", "game screen");
    im.addCommentToSection("game option", "this is a cool comment");
    im.removeParamFromSection("height", "resolution");
    im.changeParamInSection("full screen", "false", "game screen");
    im.writeFile("configTest.ini");
    im.readFile("configTest.ini");
    EXPECT_TRUE(im.getConfiguration().find("screen") == im.getConfiguration().end());
    EXPECT_TRUE(im.getConfiguration().find("game screen") != im.getConfiguration().end());
    EXPECT_TRUE(im.getConfiguration().find("resolution") != im.getConfiguration().end());
    EXPECT_TRUE(im.getConfiguration().find("game option") != im.getConfiguration().end());
    EXPECT_EQ(im.getParamValueInSection("sensibility", "game option"), "0.5");
    EXPECT_EQ(im.getParamValueInSection("aimbot", "game option"), "true");
    EXPECT_EQ(im.getParamValueInSection("full screen", "game screen"), "false");
    EXPECT_EQ(im.getParamValueInSection("width", "resolution"), "1720");
    EXPECT_TRUE(im.getConfiguration().at("resolution")->find("height") == im.getConfiguration().at("resolution")->end());
    EXPECT_EQ(im.getCommentFromSection("game screen"), "commento a caso");
    EXPECT_EQ(im.getCommentFromSection("game option"), "this is a cool comment");
}
