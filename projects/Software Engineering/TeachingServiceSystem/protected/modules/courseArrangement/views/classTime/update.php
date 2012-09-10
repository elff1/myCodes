<?php
$this->breadcrumbs=array(
	'Class Times'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>Yii::t('courseArrangement','List ClassTime'), 'url'=>array('index')),
	array('label'=>Yii::t('courseArrangement','Create ClassTime'), 'url'=>array('create')),
	array('label'=>Yii::t('courseArrangement','Manage ClassTime'), 'url'=>array('admin')),
);
?>

<h1>Update ClassTime <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>