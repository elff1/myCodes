<?php
$this->breadcrumbs=array(
	InformationManagementModule::t('courseWaitlist','Course Waitlists')=>array('index'),
	InformationManagementModule::t('courseWaitlist','View'),
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('courseWaitlist','List CourseWaitlist'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Create CourseWaitlist'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Update CourseWaitlist'), 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>InformationManagementModule::t('courseWaitlist','Delete CourseWaitlist'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>InformationManagementModule::t('courseWaitlist','Manage CourseWaitlist'), 'url'=>array('admin')),
);
?>
<h1><?php echo CHtml::encode(InformationManagementModule::t('courseWaitlist', 'View CourseWaitlist')); ?></h1>
<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'name',
		'credit',
		'class',
		'prerequsite_required',
		'introduction',
		'syllabus',
		'statement',
		'department_id',
		'priority',
	),
)); ?>
