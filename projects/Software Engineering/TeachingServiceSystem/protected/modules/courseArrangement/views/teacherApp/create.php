<?php
$this->breadcrumbs=array(
	'Teacher Apps'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'Quary application'), 'url'=>array('index')),

);
?>

<h1>Create TeacherApp</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>