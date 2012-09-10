<?php
$this->breadcrumbs=array(
	ResourceModule::t('resResource','Res Resources')=>array('index','uid'=>Yii::app()->user->id),
	ResourceModule::t('resResource','Create'),
);

$this->menu=array(
	array('label'=>ResourceModule::t('resResource','List ResResource'), 'url'=>array('index', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Manage ResResource'), 'url'=>array('admin', 'uid'=>Yii::app()->user->id)),
);
?>


<h1>
<?php 
echo ResourceModule::t('resResource','Create ResResource');
?>
</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model, )); ?>