<?php
$this->breadcrumbs=array(
	'Class Times',
);

$this->menu=array(
	array('label'=>Yii::t('courseArrangement','List ClassTime'), 'url'=>array('index')),
	array('label'=>Yii::t('courseArrangement','Create ClassTime'), 'url'=>array('create')),
	array('label'=>Yii::t('courseArrangement','Manage ClassTime'), 'url'=>array('admin')),
);
?>

<h1><?php echo Yii::t('courseArrangement','List ClassTime') ?></h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
