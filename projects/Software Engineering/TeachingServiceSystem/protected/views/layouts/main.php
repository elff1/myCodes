<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta name="language" content="en" />

	<!-- blueprint CSS framework -->
	<link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/screen.css" media="screen, projection" />
	<link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/print.css" media="print" />
	<!--[if lt IE 8]>
	<link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/ie.css" media="screen, projection" />
	<![endif]-->

	<link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/main.css" />
	<link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/form.css" />

	<title><?php echo CHtml::encode($this->pageTitle); ?></title>
</head>

<body>
<div class="container" id="page">

	<div id="header">
		<div id="logo"><a href="<?php echo Yii::app()->request->baseUrl; ?>" style="text-decoration:none;"><?php echo CHtml::encode(Yii::t('base',Yii::app()->name)); ?></a></div>
	</div><!-- header -->

	<div id="mainMbMenu">
		<?php $this->widget('application.extensions.mbmenu.MbMenu',array(
			'items'=>array(
				//array('label'=>'Home', 'url'=>array('/site/index')),
				//array('label'=>Yii::t('base','About'), 'url'=>array('/site/page', 'view'=>'about')),
				//array('label'=>'Contact', 'url'=>array('/site/contact')),
				array('label'=>Yii::t('base','Login'), 'url'=>array('/site/login'), 'visible'=>Yii::app()->user->isGuest),
				array('label'=>Yii::t('base','Logout').'('.((!Yii::app()->user->isGuest) ? Yii::app()->user->userName:'Guest') .')'.
				'('. ((!Yii::app()->user->isGuest) ? Yii::t('user',UserAuthentication::model()->typeOptions[Yii::app()->user->type]):'Guest').')', 
				'url'=>array('/site/logout'), 'visible'=>!Yii::app()->user->isGuest),
				
				array('label'=>Yii::t('base','Change Password'), 'url'=>array('/site/changePassword'), 'visible'=>!Yii::app()->user->isGuest),
				////
				
				array('label'=>Yii::t('base','Change Personal Information'), 'url'=>array('/informationManagement/personalInfo/update', 
				'id'=>Yii::app()->user->isGuest?'#':Yii::app()->user->personalInfoID), 'visible'=>!Yii::app()->user->isGuest),
				
				array(
					'label'=>Yii::t('base','Information Management'), 'items'=>
					array(
						array('label'=>Yii::t('base','Course List')/*.'(done)'*/, 'url'=>array('/informationManagement/courseBasicInfo/list')),
						//array('label'=>Yii::t('base','Study Plan')/*.'(ing)''*/, 'url'=>array('/informationManagement/programDetail')),
						array('label'=>Yii::t('base','Personal Information')/*.'(done)'*/, 'url'=>array('/informationManagement/personalInfo')),
						array('label'=>Yii::t('base','Student Basic Information')/*.'(done)'*/, 'url'=>array('/informationManagement/studentBasicInfo')),
						array('label'=>Yii::t('base','Teacher Basic Information')/*.'(done)'*/, 'url'=>array('/informationManagement/teacherBasicInfo')),
						array('label'=>Yii::t('base','Administrator Basic Information')/*.'(done)'*/, 'url'=>array('/informationManagement/adminBasicInfo')),
						array('label'=>Yii::t('base','System Administrator Basic Information')/*.'(done)'*/, 'url'=>array('/informationManagement/systemAdminBasicInfo')),
						array('label'=>Yii::t('base','Class Manage')/*.'(done)'*/, 'url'=>array('/informationManagement/classBasicInfo')),
						array('label'=>Yii::t('base','Course Basic Information'), 'url'=>array('/informationManagement/courseBasicInfo')),
						array('label'=>Yii::t('base','Course Waitlist'), 'url'=>array('/informationManagement/courseWaitlist')),
						////
						array('label'=>Yii::t('base','Authorization Management')/*.'(done)'*/, 'url'=>array('/rights')),
						array('label'=>Yii::t('base','Programs')/*.'(ing)''*/, 'url'=>array('/informationManagement/program')),
						//array('label'=>Yii::t('base','Classrooms').'(no longer available)', 'url'=>array('/informationManagement/classroomBasicInfo')),
						array('label'=>Yii::t('base','Departments')/*.'(done)'*/, 'url'=>array('/informationManagement/department')),
						array('label'=>Yii::t('base','System Log'), 'url'=>array('/informationManagement/log'),'visible'=>!Yii::app()->user->isGuest && Yii::app()->user->type==UserAuthentication::TYPE_SYSTEM_ADMIN),
						array('label'=>Yii::t('base', 'System Parameters'), 'url'=>array('/informationManagement/systemParameters'),
						'visible'=>!Yii::app()->user->isGuest && Yii::app()->user->type==UserAuthentication::TYPE_SYSTEM_ADMIN),
						array('label'=>Yii::t('base','Powered by Red_1')),
					),
				),
				
				
				array('label'=>Yii::t('base','Test Online Subsystem'), 'url'=>array('/testOnline')),
                array('label'=>Yii::t('base', 'Resource Sharing Subsystem'), 'url'=>array('/resource')),
				array('label'=>Yii::t('base', 'Course Arrangement Subsystem'), 'url'=>array('/courseArrangement')),
				array('label'=>Yii::t('base', 'Apply Class'), 'url'=>array('/courseArrangement/teacherApp')),
				array('label'=>Yii::t('base', 'Classroom Management'), 'url'=>array('/courseArrangement/classroomBasicInfo')),
				array('label'=>Yii::t('base', 'Course Selection'), 'url'=>array('/CourseSelection/default')),
				array('label'=>Yii::t('base', 'Score Management'), 'url'=>array('/courseArrangement/teacherApp')),

			),
		)); ?>
	</div><!-- mainmenu -->
	<?php if(isset($this->breadcrumbs)):?>
		<?php $this->widget('zii.widgets.CBreadcrumbs', array(
			'links'=>$this->breadcrumbs,
		)); ?><!-- breadcrumbs -->
	<?php endif?>

	<?php echo $content; ?>

	<div class="clear"></div>

	<div id="footer">
		Copyright &copy; <?php echo date('Y'); ?> by Red Group.<br/>
		All Rights Reserved.<br/>
		<?php //echo Yii::powered(); ?>
	</div><!-- footer -->

</div><!-- page -->

</body>
</html>
