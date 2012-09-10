<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('courseWaitlist','Course Waitlists')=>array('index'),
	InformationManagementModule::t('courseWaitlist','Create'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('courseWaitlist','List CourseWaitlist'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Manage CourseWaitlist'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('courseWaitlist', 'Create CourseWaitlist')); ?></h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>