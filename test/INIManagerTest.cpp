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
    EXPECT_EQ(im.getCommentFromSection("screen"), "Comment not found");
    im.addCommentToSection("this is a comment", "screen");
    EXPECT_EQ(im.getCommentFromSection("screen"), "this is a comment");
    im.addSection("resolution");
    EXPECT_EQ(im.findParamSection("full screen"), "screen");
    im.changeParamInSection("full screen", "false", "screen");
    EXPECT_EQ(im.getParamValueInSection("full screen", "screen"), "false");
    im.changeSectionName("screen", "game screen");
    EXPECT_TRUE(im.getConfiguration().find("game screen") != im.getConfiguration().end());
    EXPECT_TRUE(im.getConfiguration().at("game screen")->find("full screen") != im.getConfiguration().at("game screen")->end());
    EXPECT_EQ(im.getParamValueInSection("full screen", "game scsreen"), "false");
    EXPECT_EQ(im.getCommentFromSection("game screen"), "this is a comment");
    im.changeCommentInSection("this is another comment", "game screen");
    EXPECT_EQ(im.getCommentFromSection("game screen"), "this is another comment");
    im.removeParamFromSection("full screen", "game screen");
    EXPECT_TRUE(im.getConfiguration().at("screen")->find("full screen") == im.getConfiguration().at("screen")->end());
    im.removeCommentFromSection("game screen");
    EXPECT_EQ(im.getCommentFromSection("game screen"), "Comment not found");
    im.removeSection("game screen");
    EXPECT_TRUE(im.getConfiguration().find("game screen") == im.getConfiguration().end());
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
