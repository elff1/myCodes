-- phpMyAdmin SQL Dump
-- version 3.4.10.1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2012 年 05 月 14 日 05:01
-- 服务器版本: 5.5.20
-- PHP 版本: 5.3.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `teaching_service_system`
--

-- --------------------------------------------------------

--
-- 表的结构 `admin_basic_info`
--

CREATE TABLE IF NOT EXISTS `admin_basic_info` (
  `id` int(11) unsigned NOT NULL,
  `admin_id` char(10) NOT NULL,
  `personal_info_id` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `system_admin_id` (`admin_id`),
  KEY `personal_info_id` (`personal_info_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `admin_basic_info`
--

INSERT INTO `admin_basic_info` (`id`, `admin_id`, `personal_info_id`) VALUES
(4, 'admin', NULL);

-- --------------------------------------------------------

--
-- 表的结构 `authassignment`
--

CREATE TABLE IF NOT EXISTS `authassignment` (
  `itemname` varchar(64) NOT NULL,
  `userid` varchar(64) NOT NULL,
  `bizrule` text,
  `data` text,
  PRIMARY KEY (`itemname`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `authassignment`
--

INSERT INTO `authassignment` (`itemname`, `userid`, `bizrule`, `data`) VALUES
('SystemAdmin', '1', NULL, 'N;');

-- --------------------------------------------------------

--
-- 表的结构 `authitem`
--

CREATE TABLE IF NOT EXISTS `authitem` (
  `name` varchar(64) NOT NULL,
  `type` int(11) NOT NULL,
  `description` text,
  `bizrule` text,
  `data` text,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `authitem`
--

INSERT INTO `authitem` (`name`, `type`, `description`, `bizrule`, `data`) VALUES
('Authenticated', 2, NULL, NULL, 'N;'),
('Guest', 2, NULL, NULL, 'N;'),
('SystemAdmin', 2, NULL, NULL, 'N;');

-- --------------------------------------------------------

--
-- 表的结构 `authitemchild`
--

CREATE TABLE IF NOT EXISTS `authitemchild` (
  `parent` varchar(64) NOT NULL,
  `child` varchar(64) NOT NULL,
  PRIMARY KEY (`parent`,`child`),
  KEY `child` (`child`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `city`
--

CREATE TABLE IF NOT EXISTS `city` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `pid` int(11) unsigned NOT NULL,
  `name` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `province_id` (`pid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=415 ;

--
-- 转存表中的数据 `city`
--

INSERT INTO `city` (`id`, `pid`, `name`) VALUES
(1, 0, '北京市'),
(2, 0, '上海市'),
(3, 0, '天津市'),
(4, 0, '重庆市'),
(5, 0, '河北省'),
(6, 0, '山西省'),
(7, 0, '内蒙古自治区'),
(8, 0, '辽宁省'),
(9, 0, '吉林省'),
(10, 0, '黑龙江省'),
(11, 0, '江苏省'),
(12, 0, '浙江省'),
(13, 0, '安徽省'),
(14, 0, '福建省'),
(15, 0, '江西省'),
(16, 0, '山东省'),
(17, 0, '河南省'),
(18, 0, '湖北省'),
(19, 0, '湖南省'),
(20, 0, '广东省'),
(21, 0, '广西壮族自治区'),
(22, 0, '海南省'),
(23, 0, '四川省'),
(24, 0, '贵州省'),
(25, 0, '云南省'),
(26, 0, '西藏自治区'),
(27, 0, '陕西省'),
(28, 0, '甘肃省'),
(29, 0, '青海省'),
(30, 0, '宁夏回族自治区'),
(31, 0, '新疆维吾尔自治区'),
(32, 0, '台湾省'),
(33, 0, '香港特别行政区'),
(34, 0, '澳门特别行政区'),
(35, 5, '石家庄市'),
(36, 5, '唐山市'),
(37, 5, '秦皇岛市'),
(38, 5, '邯郸市'),
(39, 5, '邢台市'),
(40, 5, '保定市'),
(41, 5, '张家口市'),
(42, 5, '承德市'),
(43, 5, '沧州市'),
(44, 5, '廊坊市'),
(45, 5, '衡水市'),
(46, 6, '太原市'),
(47, 6, '大同市'),
(48, 6, '阳泉市'),
(49, 6, '长治市'),
(50, 6, '晋城市'),
(51, 6, '朔州市'),
(52, 6, '晋中市'),
(53, 6, '运城市'),
(54, 6, '忻州市'),
(55, 6, '临汾市'),
(56, 6, '吕梁市'),
(57, 7, '呼和浩特市'),
(58, 7, '包头市'),
(59, 7, '乌海市'),
(60, 7, '赤峰市'),
(61, 7, '通辽市'),
(62, 7, '鄂尔多斯市'),
(63, 7, '呼伦贝尔市'),
(64, 7, '巴彦淖尔市'),
(65, 7, '乌兰察布市'),
(66, 7, '兴安盟'),
(67, 7, '锡林郭勒盟'),
(68, 7, '阿拉善盟'),
(69, 8, '沈阳市'),
(70, 8, '大连市'),
(71, 8, '鞍山市'),
(72, 8, '抚顺市'),
(73, 8, '本溪市'),
(74, 8, '丹东市'),
(75, 8, '锦州市'),
(76, 8, '营口市'),
(77, 8, '阜新市'),
(78, 8, '辽阳市'),
(79, 8, '盘锦市'),
(80, 8, '铁岭市'),
(81, 8, '朝阳市'),
(82, 8, '葫芦岛市'),
(83, 9, '长春市'),
(84, 9, '吉林市'),
(85, 9, '四平市'),
(86, 9, '辽源市'),
(87, 9, '通化市'),
(88, 9, '白山市'),
(89, 9, '松原市'),
(90, 9, '白城市'),
(91, 9, '延边朝鲜族自治州'),
(92, 10, '哈尔滨市'),
(93, 10, '齐齐哈尔市'),
(94, 10, '鸡西市'),
(95, 10, '鹤岗市'),
(96, 10, '双鸭山市'),
(97, 10, '大庆市'),
(98, 10, '伊春市'),
(99, 10, '佳木斯市'),
(100, 10, '七台河市'),
(101, 10, '牡丹江市'),
(102, 10, '黑河市'),
(103, 10, '绥化市'),
(104, 10, '大兴安岭地区'),
(105, 11, '南京市'),
(106, 11, '无锡市'),
(107, 11, '徐州市'),
(108, 11, '常州市'),
(109, 11, '苏州市'),
(110, 11, '南通市'),
(111, 11, '连云港市'),
(112, 11, '淮安市'),
(113, 11, '盐城市'),
(114, 11, '扬州市'),
(115, 11, '镇江市'),
(116, 11, '泰州市'),
(117, 11, '宿迁市'),
(118, 12, '杭州市'),
(119, 12, '宁波市'),
(120, 12, '温州市'),
(121, 12, '嘉兴市'),
(122, 12, '湖州市'),
(123, 12, '绍兴市'),
(124, 12, '金华市'),
(125, 12, '衢州市'),
(126, 12, '舟山市'),
(127, 12, '台州市'),
(128, 12, '丽水市'),
(129, 13, '合肥市'),
(130, 13, '芜湖市'),
(131, 13, '蚌埠市'),
(132, 13, '淮南市'),
(133, 13, '马鞍山市'),
(134, 13, '淮北市'),
(135, 13, '铜陵市'),
(136, 13, '安庆市'),
(137, 13, '黄山市'),
(138, 13, '滁州市'),
(139, 13, '阜阳市'),
(140, 13, '宿州市'),
(141, 13, '巢湖市'),
(142, 13, '六安市'),
(143, 13, '亳州市'),
(144, 13, '池州市'),
(145, 13, '宣城市'),
(146, 14, '福州市'),
(147, 14, '厦门市'),
(148, 14, '莆田市'),
(149, 14, '三明市'),
(150, 14, '泉州市'),
(151, 14, '漳州市'),
(152, 14, '南平市'),
(153, 14, '龙岩市'),
(154, 14, '宁德市'),
(155, 15, '南昌市'),
(156, 15, '景德镇市'),
(157, 15, '萍乡市'),
(158, 15, '九江市'),
(159, 15, '新余市'),
(160, 15, '鹰潭市'),
(161, 15, '赣州市'),
(162, 15, '吉安市'),
(163, 15, '宜春市'),
(164, 15, '抚州市'),
(165, 15, '上饶市'),
(166, 16, '济南市'),
(167, 16, '青岛市'),
(168, 16, '淄博市'),
(169, 16, '枣庄市'),
(170, 16, '东营市'),
(171, 16, '烟台市'),
(172, 16, '潍坊市'),
(173, 16, '济宁市'),
(174, 16, '泰安市'),
(175, 16, '威海市'),
(176, 16, '日照市'),
(177, 16, '莱芜市'),
(178, 16, '临沂市'),
(179, 16, '德州市'),
(180, 16, '聊城市'),
(181, 16, '滨州市'),
(182, 16, '荷泽市'),
(183, 17, '郑州市'),
(184, 17, '开封市'),
(185, 17, '洛阳市'),
(186, 17, '平顶山市'),
(187, 17, '安阳市'),
(188, 17, '鹤壁市'),
(189, 17, '新乡市'),
(190, 17, '焦作市'),
(191, 17, '濮阳市'),
(192, 17, '许昌市'),
(193, 17, '漯河市'),
(194, 17, '三门峡市'),
(195, 17, '南阳市'),
(196, 17, '商丘市'),
(197, 17, '信阳市'),
(198, 17, '周口市'),
(199, 17, '驻马店市'),
(200, 17, '济源市'),
(201, 18, '武汉市'),
(202, 18, '黄石市'),
(203, 18, '十堰市'),
(204, 18, '宜昌市'),
(205, 18, '襄阳市'),
(206, 18, '鄂州市'),
(207, 18, '荆门市'),
(208, 18, '孝感市'),
(209, 18, '荆州市'),
(210, 18, '黄冈市'),
(211, 18, '咸宁市'),
(212, 18, '随州市'),
(213, 18, '恩施土家族苗族自治州'),
(214, 18, '仙桃市'),
(215, 18, '潜江市'),
(216, 18, '天门市'),
(217, 18, '神农架林区'),
(218, 19, '长沙市'),
(219, 19, '株洲市'),
(220, 19, '湘潭市'),
(221, 19, '衡阳市'),
(222, 19, '邵阳市'),
(223, 19, '岳阳市'),
(224, 19, '常德市'),
(225, 19, '张家界市'),
(226, 19, '益阳市'),
(227, 19, '郴州市'),
(228, 19, '永州市'),
(229, 19, '怀化市'),
(230, 19, '娄底市'),
(231, 19, '湘西土家族苗族自治州'),
(232, 20, '广州市'),
(233, 20, '深圳市'),
(234, 20, '珠海市'),
(235, 20, '汕头市'),
(236, 20, '韶关市'),
(237, 20, '佛山市'),
(238, 20, '江门市'),
(239, 20, '湛江市'),
(240, 20, '茂名市'),
(241, 20, '肇庆市'),
(242, 20, '惠州市'),
(243, 20, '梅州市'),
(244, 20, '汕尾市'),
(245, 20, '河源市'),
(246, 20, '阳江市'),
(247, 20, '清远市'),
(248, 20, '东莞市'),
(249, 20, '中山市'),
(250, 20, '潮州市'),
(251, 20, '揭阳市'),
(252, 20, '云浮市'),
(253, 21, '南宁市'),
(254, 21, '柳州市'),
(255, 21, '桂林市'),
(256, 21, '梧州市'),
(257, 21, '北海市'),
(258, 21, '防城港市'),
(259, 21, '钦州市'),
(260, 21, '贵港市'),
(261, 21, '玉林市'),
(262, 21, '百色市'),
(263, 21, '贺州市'),
(264, 21, '河池市'),
(265, 21, '来宾市'),
(266, 21, '崇左市'),
(267, 22, '海口市'),
(268, 22, '三亚市'),
(269, 22, '五指山市'),
(270, 22, '琼海市'),
(271, 22, '儋州市'),
(272, 22, '文昌市'),
(273, 22, '万宁市'),
(274, 22, '东方市'),
(275, 22, '澄迈县'),
(276, 22, '定安县'),
(277, 22, '屯昌县'),
(278, 22, '临高县'),
(279, 22, '白沙黎族自治县'),
(280, 22, '昌江黎族自治县'),
(281, 22, '乐东黎族自治县'),
(282, 22, '陵水黎族自治县'),
(283, 22, '保亭黎族苗族自治县'),
(284, 22, '琼中黎族苗族自治县'),
(285, 23, '成都市'),
(286, 23, '自贡市'),
(287, 23, '攀枝花市'),
(288, 23, '泸州市'),
(289, 23, '德阳市'),
(290, 23, '绵阳市'),
(291, 23, '广元市'),
(292, 23, '遂宁市'),
(293, 23, '内江市'),
(294, 23, '乐山市'),
(295, 23, '南充市'),
(296, 23, '眉山市'),
(297, 23, '宜宾市'),
(298, 23, '广安市'),
(299, 23, '达州市'),
(300, 23, '雅安市'),
(301, 23, '巴中市'),
(302, 23, '资阳市'),
(303, 23, '阿坝藏族羌族自治州'),
(304, 23, '甘孜藏族自治州'),
(305, 23, '凉山彝族自治州'),
(306, 24, '贵阳市'),
(307, 24, '六盘水市'),
(308, 24, '遵义市'),
(309, 24, '安顺市'),
(310, 24, '铜仁地区'),
(311, 24, '毕节地区'),
(312, 24, '黔西南布依族苗族自治州'),
(313, 24, '黔东南苗族侗族自治州'),
(314, 24, '黔南布依族苗族自治州'),
(315, 25, '昆明市'),
(316, 25, '曲靖市'),
(317, 25, '玉溪市'),
(318, 25, '保山市'),
(319, 25, '昭通市'),
(320, 25, '丽江市'),
(321, 25, '普洱市'),
(322, 25, '临沧市'),
(323, 25, '楚雄彝族自治州'),
(324, 25, '红河哈尼族彝族自治州'),
(325, 25, '文山壮族苗族自治州'),
(326, 25, '西双版纳傣族自治州'),
(327, 25, '大理白族自治州'),
(328, 25, '德宏傣族景颇族自治州'),
(329, 25, '怒江傈僳族自治州'),
(330, 25, '迪庆藏族自治州'),
(331, 26, '拉萨市'),
(332, 26, '昌都地区'),
(333, 26, '林芝地区'),
(334, 26, '山南地区'),
(335, 26, '日喀则地区'),
(336, 26, '那曲地区'),
(337, 26, '阿里地区'),
(338, 27, '西安市'),
(339, 27, '铜川市'),
(340, 27, '宝鸡市'),
(341, 27, '咸阳市'),
(342, 27, '渭南市'),
(343, 27, '延安市'),
(344, 27, '汉中市'),
(345, 27, '榆林市'),
(346, 27, '安康市'),
(347, 27, '商洛市'),
(348, 28, '兰州市'),
(349, 28, '嘉峪关市'),
(350, 28, '金昌市'),
(351, 28, '白银市'),
(352, 28, '天水市'),
(353, 28, '武威市'),
(354, 28, '张掖市'),
(355, 28, '平凉市'),
(356, 28, '酒泉市'),
(357, 28, '庆阳市'),
(358, 28, '定西市'),
(359, 28, '陇南市'),
(360, 28, '临夏回族自治州'),
(361, 28, '甘南藏族自治州'),
(362, 29, '西宁市'),
(363, 29, '海东地区'),
(364, 29, '海北藏族自治州'),
(365, 29, '黄南藏族自治州'),
(366, 29, '海南藏族自治州'),
(367, 29, '果洛藏族自治州'),
(368, 29, '玉树藏族自治州'),
(369, 29, '海西蒙古族藏族自治州'),
(370, 30, '银川市'),
(371, 30, '石嘴山市'),
(372, 30, '吴忠市'),
(373, 30, '固原市'),
(374, 30, '中卫市'),
(375, 31, '乌鲁木齐市'),
(376, 31, '克拉玛依市'),
(377, 31, '吐鲁番地区'),
(378, 31, '哈密地区'),
(379, 31, '昌吉回族自治州'),
(380, 31, '博尔塔拉蒙古自治州'),
(381, 31, '巴音郭楞蒙古自治州'),
(382, 31, '阿克苏地区'),
(383, 31, '克孜勒苏柯尔克孜自治州'),
(384, 31, '喀什地区'),
(385, 31, '和田地区'),
(386, 31, '伊犁哈萨克自治州'),
(387, 31, '塔城地区'),
(388, 31, '阿勒泰地区'),
(389, 31, '石河子市'),
(390, 31, '阿拉尔市'),
(391, 31, '图木舒克市'),
(392, 31, '五家渠市'),
(393, 32, '台北市'),
(394, 32, '高雄市'),
(395, 32, '基隆市'),
(396, 32, '台中市'),
(397, 32, '台南市'),
(398, 32, '新竹市'),
(399, 32, '嘉义市'),
(400, 32, '台北县'),
(401, 32, '宜兰县'),
(402, 32, '桃园县'),
(403, 32, '新竹县'),
(404, 32, '苗栗县'),
(405, 32, '台中县'),
(406, 32, '彰化县'),
(407, 32, '南投县'),
(408, 32, '云林县'),
(409, 32, '嘉义县'),
(410, 32, '台南县'),
(411, 32, '高雄县'),
(412, 32, '屏东县'),
(413, 32, '台东县'),
(414, 32, '花莲县');

-- --------------------------------------------------------

--
-- 表的结构 `classroom_basic_info`
--

CREATE TABLE IF NOT EXISTS `classroom_basic_info` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `room_number` char(11) DEFAULT NULL,
  `location` char(16) DEFAULT NULL COMMENT '西一, 西二啥的, 可以考虑 enum',
  `campus` int(11) DEFAULT NULL COMMENT 'enum',
  `type` int(11) DEFAULT NULL COMMENT '教室的类型, enum',
  `capacity` int(11) unsigned DEFAULT NULL COMMENT '最大人数',
  `college` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='教室基本信息' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `class_basic_info`
--

CREATE TABLE IF NOT EXISTS `class_basic_info` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` char(16) DEFAULT '',
  `grade` year(4) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='班级基本信息' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `class_teacher`
--

CREATE TABLE IF NOT EXISTS `class_teacher` (
  `id` int(11) NOT NULL,
  `teacherid` char(10) NOT NULL,
  `classid` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `teacherid` (`teacherid`),
  KEY `classid` (`classid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `class_time`
--

CREATE TABLE IF NOT EXISTS `class_time` (
  `id` int(11) NOT NULL,
  `class_id` int(11) NOT NULL,
  `classroom_id` int(11) unsigned NOT NULL,
  `time` int(11) NOT NULL,
  `isSingle` int(1) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `class_id1` (`class_id`),
  KEY `class_time4` (`classroom_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `course_basic_info`
--

CREATE TABLE IF NOT EXISTS `course_basic_info` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `course_id` char(9) NOT NULL DEFAULT '' COMMENT '给人看的',
  `name` char(32) DEFAULT NULL,
  `credit` float DEFAULT NULL,
  `class` int(11) DEFAULT NULL COMMENT '课程归属...大类，专业，思政啥的',
  `prerequsite_required` tinyint(1) DEFAULT NULL COMMENT '预修要求',
  `introduction` varchar(2048) DEFAULT NULL COMMENT '课程简介',
  `syllabus` varchar(2048) DEFAULT NULL COMMENT '教学大纲',
  `department_id` int(11) unsigned DEFAULT NULL COMMENT '开课学院',
  `priority` tinyint(11) unsigned DEFAULT NULL COMMENT 'private, for course arrangement',
  PRIMARY KEY (`id`),
  UNIQUE KEY `course_id` (`course_id`),
  KEY `department_id` (`department_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='课程基本信息' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `course_sel_app_byelection`
--

CREATE TABLE IF NOT EXISTS `course_sel_app_byelection` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `STU_ID` int(10) unsigned NOT NULL,
  `CLASS_ID` int(11) NOT NULL,
  `COMFIRMED` char(1) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `STU_ID` (`STU_ID`),
  KEY `CLASS_ID` (`CLASS_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `course_sel_app_normal`
--

CREATE TABLE IF NOT EXISTS `course_sel_app_normal` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `STU_ID` int(10) unsigned NOT NULL,
  `CLASS_ID` int(11) NOT NULL,
  `VOL_LV` int(11) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `STU_ID` (`STU_ID`),
  KEY `CLASS_ID` (`CLASS_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `course_sel_sched`
--

CREATE TABLE IF NOT EXISTS `course_sel_sched` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `STU_ID` int(11) unsigned NOT NULL,
  `CLASS_ID` int(11) NOT NULL,
  `REQUIRED` char(1) NOT NULL,
  `REPEATED` char(1) NOT NULL,
  `ABANDONED` char(1) NOT NULL,
  `SCORE` int(11) NOT NULL,
  `YEAR` int(11) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `STU_ID` (`STU_ID`),
  KEY `CLASS_ID` (`CLASS_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `department`
--

CREATE TABLE IF NOT EXISTS `department` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` char(16) DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='院系' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `exam`
--

CREATE TABLE IF NOT EXISTS `exam` (
  `id` int(11) NOT NULL,
  `class_id` int(11) NOT NULL,
  `classroom_id` int(11) unsigned NOT NULL,
  `teacher1_id` char(10) NOT NULL,
  `teacher2_id` char(10) NOT NULL,
  `exam_time` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `teacher1_id` (`teacher1_id`),
  KEY `teacher2_id` (`teacher2_id`),
  KEY `class_id2` (`class_id`),
  KEY `classroom_id2` (`classroom_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `paper`
--

CREATE TABLE IF NOT EXISTS `paper` (
  `id` bigint(15) unsigned NOT NULL AUTO_INCREMENT COMMENT '无意义主键',
  `paper_id` int(10) unsigned NOT NULL COMMENT '试卷号',
  `pro_id` bigint(20) unsigned NOT NULL COMMENT '题目',
  `pro_score` tinyint(4) unsigned NOT NULL COMMENT '题目分值',
  PRIMARY KEY (`id`),
  KEY `FK_paper_bank_1` (`paper_id`) USING BTREE,
  KEY `FK_paper_2` (`pro_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='试卷' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `paper_bank`
--

CREATE TABLE IF NOT EXISTS `paper_bank` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '试卷号',
  `teacher_id` int(10) unsigned NOT NULL COMMENT '教师代码',
  `course_id` int(10) unsigned NOT NULL COMMENT '课程代号',
  `is_publish` tinyint(1) DEFAULT '0' COMMENT '是否发布',
  `timelimit` time NOT NULL COMMENT '限定计时',
  PRIMARY KEY (`id`),
  KEY `FK_paper_bank_1` (`teacher_id`),
  KEY `FK_paper_bank_2` (`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='试卷库' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `personal_info`
--

CREATE TABLE IF NOT EXISTS `personal_info` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `first_name` char(8) DEFAULT NULL COMMENT '可以考虑把姓名合起来，如果测试不方便',
  `last_name` char(8) DEFAULT NULL,
  `sex` tinyint(2) DEFAULT NULL COMMENT '0,1,2 for male, female, unknown~',
  `photo` char(32) DEFAULT NULL COMMENT '存在数据库外面',
  `date_of_birth` date DEFAULT NULL,
  `ethnic_group` int(3) DEFAULT NULL COMMENT 'enum',
  `political_status` int(2) DEFAULT NULL COMMENT 'enum',
  `birth_place_city` char(16) DEFAULT NULL,
  `birth_place_province` char(16) DEFAULT NULL,
  `original_residence_city` char(16) DEFAULT NULL,
  `original_residence_province` char(16) DEFAULT NULL COMMENT '籍贯',
  `home_address` char(64) DEFAULT NULL,
  `home_postcode` char(6) DEFAULT NULL,
  `home_phone` char(32) DEFAULT NULL,
  `email` char(64) DEFAULT NULL,
  `phone` char(32) DEFAULT NULL,
  `identity_card_number` char(18) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='个人信息，所有类型用户共享' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `prerequisite`
--

CREATE TABLE IF NOT EXISTS `prerequisite` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `course_id` int(11) unsigned NOT NULL,
  `prerequsite_course_id` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `course_id` (`course_id`),
  KEY `prerequsite_course_id` (`prerequsite_course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='预修课程' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `program`
--

CREATE TABLE IF NOT EXISTS `program` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` char(16) DEFAULT '',
  `department_id` int(11) unsigned DEFAULT NULL COMMENT '打算做两级的',
  `length` tinyint(2) DEFAULT NULL COMMENT '学制',
  `grade` year(4) DEFAULT NULL COMMENT '年级',
  `introduction` varchar(2048) DEFAULT NULL COMMENT '简介',
  PRIMARY KEY (`id`),
  KEY `department_id` (`department_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='培养方案总述' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `program_detail`
--

CREATE TABLE IF NOT EXISTS `program_detail` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `program_id` int(11) unsigned NOT NULL,
  `course_id` int(11) unsigned NOT NULL,
  `type` int(11) DEFAULT NULL COMMENT '大类，通识，etc.',
  `required` tinyint(1) DEFAULT NULL COMMENT '必修',
  `recommended_year` tinyint(11) DEFAULT NULL COMMENT '1,2,3...  话说只有一套推荐修读可以么?',
  `recommended_term_start` int(11) DEFAULT NULL COMMENT '1,2,3,4,5 秋冬春夏短 这个和排课的商量',
  `recommended_term_end` int(11) DEFAULT NULL COMMENT '1,2,3,4,5 秋冬春夏短',
  PRIMARY KEY (`id`),
  KEY `program_id` (`program_id`),
  KEY `course_id` (`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='培养方案详情' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `question_bank`
--

CREATE TABLE IF NOT EXISTS `question_bank` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '题号',
  `teacher_id` int(10) unsigned NOT NULL COMMENT '教师ID',
  `course_id` int(10) unsigned NOT NULL COMMENT '课程代号',
  `question` varchar(500) NOT NULL COMMENT '题干，包括选项',
  `type` tinyint(3) unsigned NOT NULL COMMENT '0选择题，1判断题',
  `answer` char(1) NOT NULL COMMENT 'A/B/C/D或T/F',
  PRIMARY KEY (`id`),
  KEY `FK_question_bank_1` (`teacher_id`),
  KEY `FK_question_bank_2` (`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='题库' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `rights`
--

CREATE TABLE IF NOT EXISTS `rights` (
  `itemname` varchar(64) NOT NULL,
  `type` int(11) NOT NULL,
  `weight` int(11) NOT NULL,
  PRIMARY KEY (`itemname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `rights`
--

INSERT INTO `rights` (`itemname`, `type`, `weight`) VALUES
('Authenticated', 2, 0),
('Guest', 2, 1),
('SystemAdmin', 2, 2);

-- --------------------------------------------------------

--
-- 表的结构 `statistic`
--

CREATE TABLE IF NOT EXISTS `statistic` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '无意义主键',
  `done` tinyint(4) unsigned DEFAULT NULL COMMENT '做pro_id的总人数',
  `a` tinyint(4) unsigned DEFAULT NULL COMMENT '选A(T)的',
  `b` tinyint(4) unsigned DEFAULT NULL COMMENT '选B(F)的',
  `c` tinyint(4) unsigned DEFAULT NULL COMMENT '选C的',
  `d` tinyint(4) unsigned DEFAULT NULL COMMENT '选D的',
  `pro_id` bigint(20) unsigned NOT NULL COMMENT '题号',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_2` (`pro_id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='统计表' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `student_basic_info`
--

CREATE TABLE IF NOT EXISTS `student_basic_info` (
  `id` int(11) unsigned NOT NULL,
  `student_id` char(10) NOT NULL,
  `current_grade` year(4) DEFAULT NULL COMMENT '''所在年级''',
  `program_id` int(11) unsigned DEFAULT NULL COMMENT 'enum, 主修专业。其他的再建一张表',
  `entry_date` date DEFAULT NULL,
  `class_id` int(11) unsigned DEFAULT NULL COMMENT '班级->决定所在年级, 对于双班级的啥的，可以外联一张表',
  `remark` varchar(256) DEFAULT NULL,
  `personal_info_id` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `student_id` (`student_id`),
  KEY `program_id` (`program_id`),
  KEY `personal_info_id` (`personal_info_id`),
  KEY `class_id` (`class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='学生基本信息，只含有行政相关的列';

--
-- 转存表中的数据 `student_basic_info`
--

INSERT INTO `student_basic_info` (`id`, `student_id`, `current_grade`, `program_id`, `entry_date`, `class_id`, `remark`, `personal_info_id`) VALUES
(2, 'student', NULL, NULL, NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- 表的结构 `student_class_assignment`
--

CREATE TABLE IF NOT EXISTS `student_class_assignment` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `student_id` int(11) unsigned NOT NULL,
  `class_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `student_id` (`student_id`),
  KEY `class_id` (`class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `student_program_assignment`
--

CREATE TABLE IF NOT EXISTS `student_program_assignment` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `student_id` int(11) unsigned NOT NULL,
  `program_id` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `student_id` (`student_id`),
  KEY `program_id` (`program_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `system_admin_basic_info`
--

CREATE TABLE IF NOT EXISTS `system_admin_basic_info` (
  `id` int(11) unsigned NOT NULL,
  `system_admin_id` char(10) NOT NULL,
  `personal_info_id` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `system_admin_id` (`system_admin_id`),
  KEY `personal_info_id` (`personal_info_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `system_admin_basic_info`
--

INSERT INTO `system_admin_basic_info` (`id`, `system_admin_id`, `personal_info_id`) VALUES
(1, 'sysadmin', NULL);

-- --------------------------------------------------------

--
-- 表的结构 `teacher_app`
--

CREATE TABLE IF NOT EXISTS `teacher_app` (
  `id` int(11) NOT NULL,
  `place` varchar(45) DEFAULT NULL,
  `time` varchar(45) DEFAULT NULL,
  `courseID` char(9) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  `teacherID` char(10) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `courseID` (`courseID`),
  KEY `teacherID2` (`teacherID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `teacher_basic_info`
--

CREATE TABLE IF NOT EXISTS `teacher_basic_info` (
  `id` int(11) unsigned NOT NULL,
  `teacher_id` char(10) NOT NULL,
  `title` int(11) DEFAULT NULL COMMENT '个数商榷',
  `department_id` int(11) unsigned DEFAULT NULL,
  `personal_info_id` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `teacher_id` (`teacher_id`),
  KEY `department_id` (`department_id`),
  KEY `personal_info_id` (`personal_info_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `teacher_basic_info`
--

INSERT INTO `teacher_basic_info` (`id`, `teacher_id`, `title`, `department_id`, `personal_info_id`) VALUES
(3, 'teacher', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- 表的结构 `teachingclass_info`
--

CREATE TABLE IF NOT EXISTS `teachingclass_info` (
  `class_id` int(11) NOT NULL,
  `course_num` char(9) NOT NULL,
  `max` varchar(45) DEFAULT NULL,
  `term` varchar(45) DEFAULT NULL,
  `campus` varchar(45) DEFAULT NULL,
  `dependence` int(11) DEFAULT NULL,
  PRIMARY KEY (`class_id`),
  KEY `coursenum` (`course_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `test`
--

CREATE TABLE IF NOT EXISTS `test` (
  `id` bigint(25) unsigned NOT NULL AUTO_INCREMENT,
  `student_id` int(10) unsigned NOT NULL,
  `paper_pro_id` bigint(15) unsigned NOT NULL,
  `choose` char(1) NOT NULL,
  `is_commit` tinyint(1) NOT NULL,
  `score` tinyint(4) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_test_1` (`student_id`),
  KEY `FK_test_2` (`paper_pro_id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='学生测试' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- 表的结构 `user_authentication`
--

CREATE TABLE IF NOT EXISTS `user_authentication` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `password` char(40) NOT NULL DEFAULT '' COMMENT 'the length can be changed, depending on different encryption algorithms',
  `type` tinyint(11) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='用户验证需要的表' AUTO_INCREMENT=5 ;

--
-- 转存表中的数据 `user_authentication`
--

INSERT INTO `user_authentication` (`id`, `password`, `type`) VALUES
(1, 'sysadmin', 4),
(2, 'student', 1),
(3, 'teacher', 2),
(4, 'admin', 3);

--
-- 限制导出的表
--

--
-- 限制表 `admin_basic_info`
--
ALTER TABLE `admin_basic_info`
  ADD CONSTRAINT `admin_basic_info_ibfk_1` FOREIGN KEY (`personal_info_id`) REFERENCES `personal_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `admin_basic_info_ibfk_2` FOREIGN KEY (`id`) REFERENCES `user_authentication` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `authassignment`
--
ALTER TABLE `authassignment`
  ADD CONSTRAINT `authassignment_ibfk_1` FOREIGN KEY (`itemname`) REFERENCES `authitem` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `authitemchild`
--
ALTER TABLE `authitemchild`
  ADD CONSTRAINT `authitemchild_ibfk_1` FOREIGN KEY (`parent`) REFERENCES `authitem` (`name`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `authitemchild_ibfk_2` FOREIGN KEY (`child`) REFERENCES `authitem` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `class_teacher`
--
ALTER TABLE `class_teacher`
  ADD CONSTRAINT `classid` FOREIGN KEY (`classid`) REFERENCES `teachingclass_info` (`class_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `teacherid` FOREIGN KEY (`teacherid`) REFERENCES `teacher_basic_info` (`teacher_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `class_time`
--
ALTER TABLE `class_time`
  ADD CONSTRAINT `class_id1` FOREIGN KEY (`class_id`) REFERENCES `teachingclass_info` (`class_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `class_time4` FOREIGN KEY (`classroom_id`) REFERENCES `classroom_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `course_basic_info`
--
ALTER TABLE `course_basic_info`
  ADD CONSTRAINT `course_basic_info_ibfk_1` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `course_sel_app_byelection`
--
ALTER TABLE `course_sel_app_byelection`
  ADD CONSTRAINT `course_sel_app_byelection_ibfk_1` FOREIGN KEY (`STU_ID`) REFERENCES `student_basic_info` (`id`),
  ADD CONSTRAINT `course_sel_app_byelection_ibfk_2` FOREIGN KEY (`CLASS_ID`) REFERENCES `teachingclass_info` (`class_id`);

--
-- 限制表 `course_sel_app_normal`
--
ALTER TABLE `course_sel_app_normal`
  ADD CONSTRAINT `course_sel_app_normal_ibfk_1` FOREIGN KEY (`STU_ID`) REFERENCES `student_basic_info` (`id`),
  ADD CONSTRAINT `course_sel_app_normal_ibfk_2` FOREIGN KEY (`CLASS_ID`) REFERENCES `teachingclass_info` (`class_id`);

--
-- 限制表 `course_sel_sched`
--
ALTER TABLE `course_sel_sched`
  ADD CONSTRAINT `course_sel_sched_ibfk_1` FOREIGN KEY (`STU_ID`) REFERENCES `student_basic_info` (`id`),
  ADD CONSTRAINT `course_sel_sched_ibfk_2` FOREIGN KEY (`CLASS_ID`) REFERENCES `teachingclass_info` (`class_id`);

--
-- 限制表 `exam`
--
ALTER TABLE `exam`
  ADD CONSTRAINT `classroom_id2` FOREIGN KEY (`classroom_id`) REFERENCES `classroom_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `class_id2` FOREIGN KEY (`class_id`) REFERENCES `teachingclass_info` (`class_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `teacher1_id` FOREIGN KEY (`teacher1_id`) REFERENCES `teacher_basic_info` (`teacher_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `teacher2_id` FOREIGN KEY (`teacher2_id`) REFERENCES `teacher_basic_info` (`teacher_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `paper`
--
ALTER TABLE `paper`
  ADD CONSTRAINT `FK_paper_1` FOREIGN KEY (`paper_id`) REFERENCES `paper_bank` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_paper_2` FOREIGN KEY (`pro_id`) REFERENCES `question_bank` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `paper_bank`
--
ALTER TABLE `paper_bank`
  ADD CONSTRAINT `FK_paper_bank_1` FOREIGN KEY (`teacher_id`) REFERENCES `teacher_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_paper_bank_2` FOREIGN KEY (`course_id`) REFERENCES `course_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `prerequisite`
--
ALTER TABLE `prerequisite`
  ADD CONSTRAINT `prerequisite_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `prerequisite_ibfk_2` FOREIGN KEY (`prerequsite_course_id`) REFERENCES `course_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `program`
--
ALTER TABLE `program`
  ADD CONSTRAINT `program_ibfk_1` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `program_detail`
--
ALTER TABLE `program_detail`
  ADD CONSTRAINT `program_detail_ibfk_1` FOREIGN KEY (`program_id`) REFERENCES `program` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `program_detail_ibfk_2` FOREIGN KEY (`course_id`) REFERENCES `course_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `question_bank`
--
ALTER TABLE `question_bank`
  ADD CONSTRAINT `FK_question_bank_1` FOREIGN KEY (`teacher_id`) REFERENCES `teacher_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_question_bank_2` FOREIGN KEY (`course_id`) REFERENCES `course_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `rights`
--
ALTER TABLE `rights`
  ADD CONSTRAINT `rights_ibfk_1` FOREIGN KEY (`itemname`) REFERENCES `authitem` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `statistic`
--
ALTER TABLE `statistic`
  ADD CONSTRAINT `FK_statistic_1` FOREIGN KEY (`pro_id`) REFERENCES `question_bank` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `student_basic_info`
--
ALTER TABLE `student_basic_info`
  ADD CONSTRAINT `student_basic_info_ibfk_2` FOREIGN KEY (`program_id`) REFERENCES `program` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `student_basic_info_ibfk_3` FOREIGN KEY (`personal_info_id`) REFERENCES `personal_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `student_basic_info_ibfk_4` FOREIGN KEY (`class_id`) REFERENCES `class_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `student_basic_info_ibfk_5` FOREIGN KEY (`id`) REFERENCES `user_authentication` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `student_class_assignment`
--
ALTER TABLE `student_class_assignment`
  ADD CONSTRAINT `student_class_assignment_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `student_class_assignment_ibfk_2` FOREIGN KEY (`class_id`) REFERENCES `class_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `student_program_assignment`
--
ALTER TABLE `student_program_assignment`
  ADD CONSTRAINT `student_program_assignment_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `student_program_assignment_ibfk_2` FOREIGN KEY (`program_id`) REFERENCES `program` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `system_admin_basic_info`
--
ALTER TABLE `system_admin_basic_info`
  ADD CONSTRAINT `system_admin_basic_info_ibfk_1` FOREIGN KEY (`id`) REFERENCES `user_authentication` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `system_admin_basic_info_ibfk_2` FOREIGN KEY (`personal_info_id`) REFERENCES `personal_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `teacher_app`
--
ALTER TABLE `teacher_app`
  ADD CONSTRAINT `teacherID2` FOREIGN KEY (`teacherID`) REFERENCES `teacher_basic_info` (`teacher_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `courseID` FOREIGN KEY (`courseID`) REFERENCES `course_basic_info` (`course_id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- 限制表 `teacher_basic_info`
--
ALTER TABLE `teacher_basic_info`
  ADD CONSTRAINT `teacher_basic_info_ibfk_2` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `teacher_basic_info_ibfk_3` FOREIGN KEY (`id`) REFERENCES `user_authentication` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `teacher_basic_info_ibfk_4` FOREIGN KEY (`personal_info_id`) REFERENCES `personal_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `teachingclass_info`
--
ALTER TABLE `teachingclass_info`
  ADD CONSTRAINT `coursenum` FOREIGN KEY (`course_num`) REFERENCES `course_basic_info` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- 限制表 `test`
--
ALTER TABLE `test`
  ADD CONSTRAINT `FK_test_2` FOREIGN KEY (`paper_pro_id`) REFERENCES `paper` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_test_1` FOREIGN KEY (`student_id`) REFERENCES `student_basic_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
