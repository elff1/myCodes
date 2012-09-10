<?php
$this->breadcrumbs=array(
	'新增教室'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'View Classroom'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Create Classroom'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Manage Classroom'), 'url'=>array('admin')),
	
);
?>

<h1>新增教室</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>