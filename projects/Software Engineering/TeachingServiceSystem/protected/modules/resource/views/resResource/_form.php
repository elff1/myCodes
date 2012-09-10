<div class="form">
<?php $form=$this->beginWidget('CActiveForm', 
	array(
	'id'=>'res-resource-form',
	'enableAjaxValidation'=>false,
	'htmlOptions'=>array('enctype'=>'multipart/form-data'),
	));
?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<?php 
	//if ($model->isNewRecord)
	//{
		
		echo '<div class="row">';
		echo $form->labelEx($model,'path'); 
		echo $form->fileField($model, 'path', '');
		echo $form->error($model,'path'); 
		echo '</div>';
	//}
	?>
	<div class="row">
		<?php echo $form->labelEx($model,'display_name'); ?>
		<?php echo $form->textField($model,'display_name',array('size'=>60,'maxlength'=>255)); ?>
		<?php echo $form->error($model,'display_name'); ?>
	</div>

	<!-- 
	<div class="row">
		<?php echo $form->labelEx($model,'uploader_id'); ?>
		<?php //echo $form->textField($model,'uploader_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php echo $form->label($model, $model->uploader_id); ?>
		<?php echo $form->error($model,'uploader_id'); ?>
	</div>
	 -->
	
	<!--  
	<div class="row">
		<?php echo $form->labelEx($model,'download_count'); ?>
		<?php echo $form->textField($model,'download_count',array('size'=>10,'maxlength'=>10)); ?>
		<?php echo $form->error($model,'download_count'); ?>
	</div>
	-->
	
	<!-- 
	<div class="row">
		<?php echo $form->labelEx($model,'resource_type'); ?>
		<?php echo $form->radioButtonList($model, 'resource_type', array('normal', 'homework', 'assignment'));?>
		<?php echo $form->error($model,'resource_type'); ?>
	</div>
 	-->
	<div class="row">
		<?php echo $form->labelEx($model,'description'); ?>
		<?php echo $form->textArea($model,'description',array('size'=>60,'maxlength'=>2048)); ?>
		<?php echo $form->error($model,'description'); ?>
	</div>
	
	<!--
	<div class="row">
		<?php echo $form->labelEx($model,'upload_time'); ?>
		<?php echo $form->textField($model,'upload_time'); ?>
		<?php echo $form->error($model,'upload_time'); ?>
	</div>
	-->	

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->