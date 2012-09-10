<?php
$this->breadcrumbs=array(
	'Teachingclass Infos',
);

$this->menu=array(
	array('label'=>'Create TeachingclassInfo', 'url'=>array('create')),
	array('label'=>'Manage TeachingclassInfo', 'url'=>array('admin')),
);
?>

<h1>Teachingclass Infos</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
