<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Question Bank'=>array('index'),
		$model->id,
);

$this->menu=array(
	array('label'=>TestOnlineModule::t('core','Modify'), 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>TestOnlineModule::t('core','Delete'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>TestOnlineModule::t('core','List Questions'), 'url'=>array('index')),
	array('label'=>TestOnlineModule::t('core','Add Question'), 'url'=>array('create')),
	array('label'=>TestOnlineModule::t('core','Manage Questions'), 'url'=>array('admin')),
	array('label'=>TestOnlineModule::t('core','Batch Add Questions'), 'url'=>array('batchCreate')),
);
?>

<h1>View QuestionBank #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'question',
		'selection_a',
		'selection_b',
		'selection_c',
		'selection_d',
		'type',
		'answer',
	),
)); ?>
