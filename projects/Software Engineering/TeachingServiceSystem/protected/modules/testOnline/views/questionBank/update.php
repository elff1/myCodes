<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Question Banks'=>array('index'),
//		$model->id=>array('view','id'=>$model->id),
		'Update',
);

$this->menu=array(
	array('label'=>TestOnlineModule::t('core','Add Question'), 'url'=>array('create')),
	array('label'=>TestOnlineModule::t('core','View Question'), 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>TestOnlineModule::t('core','List Questions'), 'url'=>array('index')),
	array('label'=>TestOnlineModule::t('core','Manage Questions'), 'url'=>array('admin')),
	array('label'=>TestOnlineModule::t('core','Batch Add Questions'), 'url'=>array('batchCreate')),
);
?>

<h1>Update QuestionBank <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>
