<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('courseWaitlist','Course Waitlists'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('courseWaitlist','Course Confirm'), 'url'=>array('confirm')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Create CourseWaitlist'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Manage CourseWaitlist'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('courseWaitlist', 'Course Waitlists')); ?></h1>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
