<?php
$this->breadcrumbs=array(
	ResourceModule::t('resResource','Res Resources')=>array('index', 'uid'=>Yii::app()->user->id),
	$model->id=>array('view','id'=>$model->id),
	ResourceModule::t('resResource','Update'),
);

$this->menu=array(
	array('label'=>ResourceModule::t('resResource','List ResResource'), 'url'=>array('index', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Create ResResource'), 'url'=>array('create')),
	array('label'=>ResourceModule::t('resResource','View ResResource'), 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>ResourceModule::t('resResource','Manage ResResource'), 'url'=>array('admin', 'uid'=>Yii::app()->user->id)),
);
?>

<h1>
<?php 
echo ResourceModule::t('resResource','Update');
echo ResourceModule::t('resResource','ResResource'); 
echo $model->id; 
?>
</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model) ); ?>