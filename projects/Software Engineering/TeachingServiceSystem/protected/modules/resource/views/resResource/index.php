<?php
$this->breadcrumbs=array(
	ResourceModule::t('resResource','Res Resources'),
);


if(Yii::app()->user->type == 3 || Yii::app()->user->type == 4)
$this->menu=array(
	array('label'=>ResourceModule::t('resResource','Create ResResource'), 'url'=>array('create')),
	array('label'=>ResourceModule::t('resResource','Manage ResResource'), 'url'=>array('admin&uid='.strval((int)Yii::app()->user->id))),
	array('label'=>ResourceModule::t('resResource', 'Search ResResource'), 'url'=>array('search')),
	array('label'=>ResourceModule::t('resResource', 'Manage Comments'), 'url'=>array('comments/admin')),
);

else 
{
	$this->menu=array(
		array('label'=>ResourceModule::t('resResource','Create ResResource'), 'url'=>array('create')),
		array('label'=>ResourceModule::t('resResource','Manage ResResource'), 'url'=>array('admin&uid='.strval((int)Yii::app()->user->id))),
		array('label'=>ResourceModule::t('resResource','Search ResResource'), 'url'=>array('search')),
	);
}
?>

<?php
 echo '<h1>';
 echo ResourceModule::t('resResource','Res Resources');
 echo '</h1>';
?>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
    'sortableAttributes' => array(
        'download_count' => ResourceModule::t('resResource','Download Count'),
    ),
)); ?>
