<?php
$this->breadcrumbs=array(
	'Class Times'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>Yii::t('courseArrangement','List ClassTime'), 'url'=>array('index')),
	array('label'=>Yii::t('courseArrangement','Create ClassTime'), 'url'=>array('create')),
	array('label'=>Yii::t('courseArrangement','Manage ClassTime'), 'url'=>array('admin')),
);
?>

<h1><?php echo Yii::t('courseArrangement','Create ClassTime') ?></h1>

<?php echo $this->renderPartial('_form2', array('model'=>$model)); ?>